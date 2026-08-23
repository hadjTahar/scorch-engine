#include "graphicsview.h"
#include "graphicswindow.h"

#include "graphicsitem2d.h"
#include "graphicsitem3d.h"
#include "graphicsscene.h"

#include <utils/EntityManager.h>
#include <filament/View.h>
#include <filament/Viewport.h>

namespace Qx::prv
{


GraphicsView::GraphicsView(GraphicsScene *scene,
                           const x_rect &rc,
                           ViewType tp):
    m_rect{ rc },
    m_type{ tp },
    m_camera{ MetaObject::make_unique_meta<GraphicsCamera>(scene) },
    m_transform{ x_matrix4x4{1} }
{
    auto engine = GraphicsWindow::filamentEngine();
    m_filamentCamera = engine->createCamera(utils::EntityManager::get().create());
    m_filamentView   = engine->createView();




    // 5. Connect structural components to the viewport view

    m_filamentView->setScene(scene->filamentScene() );
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


}

GraphicsView::~GraphicsView()
{
    auto engine = GraphicsWindow::filamentEngine();
    engine->destroyCameraComponent( m_filamentCamera->getEntity() );
    engine->destroy(m_filamentView);
}

bool GraphicsView::shouldRender(GraphicsItem *itm)
{
    dbg_warning() << "You are not checking renderable items";
    // const ItemRendering rendering = rendering;
    /*
ItemRendering ::rendering
    visible     -> continue;
    clipping    -> Ignore
    culling     -> if( true ) check camera, else continue
    antilalias  -> Ignore
    lod         -> if( true ) calculate lod
*/
    return true;
}

// std::vector<GraphicsItem *> GraphicsView::renderables(const std::vector<GraphicsItem *> lst) const
// {
//     dbg_warning() << "For 2D sort by z and return";
//     return lst;
// }

void GraphicsView::applyFilamentCamera()
{
    /// ## IF 2D don't modify the filamnet camera

    const auto &camProperties = m_camera->properties;
    const auto camMd    = camProperties.mode();

    const auto camPos = camProperties.position();
    const auto camFrw = camProperties.forward();
    const auto camUp  = camProperties.up();


    if( camMd == CameraMode::PERSPECTIVE)
    {
        const auto fovInDegrees = camProperties.fieldOfView();
        const auto aspectRatio  = camProperties.aspectRatio();
        const auto near         = camProperties.nearPlane();
        const auto far          = camProperties.farPlane();

        m_filamentCamera->setProjection(
            fovInDegrees,
            aspectRatio,
            near,
            far);
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

GraphicsCamera *GraphicsView::camera() const
{
    return m_camera.get();
}

x_matrix4x4 GraphicsView::transform()
{
    return m_transform;
}

filament::View *GraphicsView::filamentView() const
{
    return m_filamentView;
}


}
