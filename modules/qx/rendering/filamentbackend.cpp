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
    m_filamentScene{ nullptr },
    m_filamentView{ nullptr },
    m_filamentCamera{ nullptr }
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

    if( m_filamentCamera ){
        m_filamentEngine->destroyCameraComponent( m_filamentCamera->getEntity() );
        m_filamentCamera = nullptr;
    }

    if( m_filamentView ){
        m_filamentEngine->destroy( m_filamentView );
        m_filamentView = nullptr;
    }

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
    clearOptions.clearColor = {1.f, 0.f, 0.f, 1.0f};
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

    if( !m_filamentView )
        m_filamentView   = m_filamentEngine->createView();

    if( !m_filamentCamera )
        m_filamentCamera = m_filamentEngine->createCamera(utils::EntityManager::get().create());

    m_filamentView->setScene( m_filamentScene );
    m_filamentView->setCamera(m_filamentCamera);
    m_filamentView->setViewport({0, 0, 1920, 1080});


    filament::BloomOptions opts;
    opts.enabled = true;
    opts.strength = .75;
    opts.blendMode = filament::BloomOptions::BlendMode::INTERPOLATE;
    opts.haloThickness = .2;
    opts.haloRadius = .1;
    // BlendMode_Dissolve
    m_filamentView->setBloomOptions( opts );


    return prv::BackendResult::SUCCESS;
}

prv::BackendResult FilamentBackend::renderGraphicsView(prv::GraphicsView *grphxView)
{
    const auto camProperties = grphxView->camera()->properties;

    m_filamentRenderer->render( m_filamentView );
    applyCamera( camProperties );
    return prv::BackendResult::SUCCESS;
}

Qx::prv::BackendResult FilamentBackend::renderMeshModel(const MeshModel *mshModel)
{
    return prv::BackendResult::SUCCESS;
}



void FilamentBackend::applyCamera(const prv::CameraProperties &camProperties)
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

        m_filamentCamera->setProjection(
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
        m_filamentCamera->setProjection( filament::Camera::Projection::ORTHO,
                                        min.x, max.x,
                                        min.y, max.y,
                                        min.z, max.z);

    }

    /// ## For 2D fix these values
    filament::math::float3 eye( camPos.x, camPos.y, camPos.z);
    filament::math::float3 center(camFrw.x, camFrw.y, camFrw.z);
    filament::math::float3 up(camUp.x, camUp.y, camUp.z);
    m_filamentCamera->lookAt(eye, center, up);
}



}
