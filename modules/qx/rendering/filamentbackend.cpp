#include "filamentbackend.h"

#include <core/graphicsview.h>
#include <core/graphicswindow.h>
#include <filament/SwapChain.h>
#include <misc/platfrom.h>


namespace Qx::Backend
{


FilamentBackend::FilamentBackend(prv::GraphicsWindow *winItm):
    prv::RenderBackendBase{ winItm },
    m_filamentSwapChain{ nullptr },
    m_filamentScene{ nullptr }
{
    dbg_assert( !m_created ) <<
        "3D only supports one FilamentBackend "
        "or one 3D scene for now";
    m_created = true;
}

FilamentBackend::~FilamentBackend()
{
    destroyScene();
    destroySwapChain();
    destroyEngine();
}

void FilamentBackend::destroyScene()
{
    if( !m_filamentEngine )
        return;


    for ( auto flmtCam : m_filamentCameras)
        m_filamentEngine->destroyCameraComponent( flmtCam->getEntity() );


    for ( auto flmtVew : m_filamentViews)
        m_filamentEngine->destroy( flmtVew );



    if( m_filamentScene ){
        m_filamentEngine->destroy( m_filamentScene );
        m_filamentScene = nullptr;
    }
}

void FilamentBackend::destroySwapChain()
{
    if( !m_filamentEngine )
        return;


    if( !m_filamentSwapChain )
        return;
    m_filamentEngine->destroy( m_filamentSwapChain );
    m_filamentEngine->flushAndWait();
    m_filamentSwapChain = nullptr;
    setWindowSwapChain( nullptr );
}

void FilamentBackend::destroyEngine()
{
    m_filamentEngine->flushAndWait();
    m_filamentEngine->destroy(m_filamentRenderer);
    filament::Engine::destroy(m_filamentEngine);

    m_filamentRenderer = nullptr;
    m_filamentEngine   = nullptr;
}
prv::BackendResult FilamentBackend::beginFrame()
{
    const auto res = m_filamentRenderer->beginFrame( m_filamentSwapChain );
    return res? prv::BackendResult::SUCCESS :
               prv::BackendResult::FAIL;
}

prv::BackendResult FilamentBackend::endFrame()
{
    m_filamentRenderer->endFrame();
    return prv::BackendResult::SUCCESS;

}

prv::BackendResult FilamentBackend::initBackend(const x_size &sz)
{
    if( !m_filamentEngine )
        m_filamentEngine = filament::Engine::create();
    dbg_assert( m_filamentEngine ) << "Invalid m_filamentEngine";

    if( !m_filamentRenderer )
        m_filamentRenderer  = m_filamentEngine->createRenderer();

    // Set up the clear options
    filament::Renderer::ClearOptions clearOptions;
    clearOptions.clearColor = {0.f, 0.f, 0.f, 1.0f};
    clearOptions.clear = true; // Enable clearing the color buffer
    clearOptions.discard = true; // Optimization: discard contents after use

    m_filamentRenderer->setClearOptions(clearOptions);

    dbg_assert( m_filamentRenderer ) << "Invalid m_filamentRenderer";

    auto winSwapChain = windowSwapChain();
    if( winSwapChain )
        m_filamentSwapChain = static_cast<filament::SwapChain*>( winSwapChain );
    else{
        auto nativeWin = prv::Platfrom::nativeWindowHandle( m_windowItem->sdlWindow() );
        m_filamentSwapChain = m_filamentEngine->createSwapChain( nativeWin );
        dbg_assert( m_filamentSwapChain ) << "Invalid m_filamentSwapChain";
        setWindowSwapChain( m_filamentSwapChain );
    }


    /// ## ------------------------------------------------------------------------

    if( !m_filamentScene )
        m_filamentScene  = m_filamentEngine->createScene();


    return prv::BackendResult::SUCCESS;
}

prv::BackendResult FilamentBackend::renderGraphicsView(prv::GraphicsView *grphxView,
                                                       x_count viewIndex)
{
    const auto cnt = m_filamentViews.size();
    dbg_assert( m_filamentCameras.size() == cnt  )  <<
        "m_filamentViews and m_filamentCameras must have the same size";

    if( viewIndex >= cnt )
        addView( grphxView );

    dbg_assert( viewIndex < m_filamentViews.size()  )  <<
        "viewIndex must be less than m_filamentViews size";

    const auto camProperties = grphxView->camera()->properties;
    auto flmntVew = m_filamentViews[viewIndex];
    auto flmntCam = m_filamentCameras[viewIndex];

    m_filamentRenderer->render( flmntVew );
    applyCamera( flmntCam, camProperties );
    return prv::BackendResult::SUCCESS;
}

prv::BackendResult FilamentBackend::addView(prv::GraphicsView *vw)
{
    // return prv::BackendResult::SUCCESS;


    dbg_assert( m_filamentEngine )  << "Invalid m_filamentEngine";
    dbg_assert( m_filamentScene )   << "Invalid m_filamentScene";

    if( !m_filamentEngine )
        return prv::BackendResult::FAIL;
    if( !m_filamentScene )
        return prv::BackendResult::FAIL;

    auto flmntVew = m_filamentEngine->createView();
    auto flmntCam = m_filamentEngine->createCamera(utils::EntityManager::get().create());


    flmntVew->setScene( m_filamentScene );
    flmntVew->setCamera(flmntCam);
    flmntVew->setViewport({0, 0, 1920, 1080});

    filament::BloomOptions opts;
    opts.enabled = true;
    opts.strength = .75;
    opts.blendMode = filament::BloomOptions::BlendMode::INTERPOLATE;
    opts.haloThickness = .2;
    opts.haloRadius = .1;
    // BlendMode_Dissolve
    flmntVew->setBloomOptions( opts );


    m_filamentViews.push_back( flmntVew );
    m_filamentCameras.push_back( flmntCam );
    return prv::BackendResult::SUCCESS;
}

Qx::prv::BackendResult FilamentBackend::renderMeshModel(const MeshModel *mshModel)
{
    return prv::BackendResult::SUCCESS;
}



void FilamentBackend::applyCamera(filament::Camera *flmntCam,
                                  const prv::CameraProperties &camProperties)
{
    /// ## IF 2D don't modify the filamnet camera

    const auto camMd    = camProperties.mode();

    const auto camPos = camProperties.position();
    const auto camFrw = camProperties.forward();
    const auto camUp  = camProperties.up();


    if( camMd == prv::CameraMode::PERSPECTIVE)
    {
        const auto fovInDegrees = camProperties.fieldOfView();
        const auto aspectRatio  = camProperties.aspectRatio();
        const auto camNear         = camProperties.nearPlane();
        const auto camFar          = camProperties.farPlane();

        flmntCam->setProjection(
            fovInDegrees,
            aspectRatio,
            camNear,
            camFar);
    }
    else
    {
        const auto orthoBox = camProperties.orthoBox();
        const auto min = orthoBox.min;
        const auto max = orthoBox.max;
        flmntCam->setProjection( filament::Camera::Projection::ORTHO,
                                        min.x, max.x,
                                        min.y, max.y,
                                        min.z, max.z);

    }

    /// ## For 2D fix these values
    filament::math::float3 eye( camPos.x, camPos.y, camPos.z);
    filament::math::float3 center(camFrw.x, camFrw.y, camFrw.z);
    filament::math::float3 up(camUp.x, camUp.y, camUp.z);
    flmntCam->lookAt(eye, center, up);
}

filament::Renderer *FilamentBackend::filamentRenderer()
{
    return m_filamentRenderer;
}

filament::Engine *FilamentBackend::filamentEngine()
{
    return m_filamentEngine;
}

filament::Scene *FilamentBackend::filamentScene() const
{
    return m_filamentScene;
}



}
