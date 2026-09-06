#include "graphicsview.h"
#include "graphicswindow.h"

#include "graphicsitem2d.h"
#include "graphicsitem3d.h"
#include "graphicsscene.h"


namespace Qx::prv
{

GraphicsView::GraphicsView(GraphicsScene *scene):
    m_viewport{ 0,0,1,1 },
    m_logicalSize{1920,1080},
    m_type{ ViewType::Relative},
    m_mode{ ViewMode::Stretch},
    m_camera{ MetaObject::make_unique_meta<GraphicsCamera>(scene) }
{


}

GraphicsView::~GraphicsView()
{
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



GraphicsCamera *GraphicsView::camera() const
{
    return m_camera.get();
}

x_matrix4x4 GraphicsView::logicalTransform(const x_size &windSz) const
{
    const auto screenSz = camera()->screen().size();

    const auto vp  = effectiveViwport( windSz );
    const auto sc0 =logicalScale( windSz );

    const auto sc1 = x_vector2{
        vp.width  / screenSz.width,
        vp.height / screenSz.height
    };


    const auto sc  = x_vector3{sc0.x*sc1.x,
                              sc0.y*sc1.y,
                              1};

    const auto idMat = x_matrix4x4{1};
    const auto trMat = x_vector::translate( idMat, {vp.x, vp.y,0} );
    const auto scMat = x_vector::scale( idMat, {sc.x, sc.y, 1 } );
    return trMat * scMat;
}

x_vector2 GraphicsView::logicalScale(const x_size &windSz) const
{
    const auto vwPort = effectiveViwport( windSz );
    const auto xx = m_logicalSize.width  / vwPort.width;
    const auto yy = m_logicalSize.height / vwPort.height;


    switch (m_mode)
    {
    case ViewMode::Stretch:
        return { xx, yy };

    case ViewMode::Fit:
    {
        const auto sc = std::min(xx, yy);
        return { sc, sc };
    }

    case ViewMode::Fill:
    {
        const auto sc = std::max(xx, yy);
        return { sc, sc };
    }
    }

    return { xx, yy };
}

x_rect GraphicsView::viewport() const
{
    return m_viewport;
}

void GraphicsView::setViewport(const x_rect &newViewport)
{
    m_viewport = newViewport;
}

x_rect GraphicsView::effectiveViwport(const x_size &windSz) const
{
    if( m_type == ViewType::Absolute )
        return viewport();


    const auto xx = m_viewport.x      * windSz.width;
    const auto yy = m_viewport.y      * windSz.height;
    const auto ww = m_viewport.width  * windSz.width;
    const auto hh = m_viewport.height * windSz.height;

    return { xx, yy, ww, hh };
}


x_size GraphicsView::logicalSize() const
{
    return m_logicalSize;
}

void GraphicsView::setLogicalSize(x_size newLogicalSize)
{
    m_logicalSize = newLogicalSize;
}

ViewType GraphicsView::type() const
{
    return m_type;
}

void GraphicsView::setType(ViewType newType)
{
    m_type = newType;
}

ViewMode GraphicsView::mode() const
{
    return m_mode;
}

void GraphicsView::setMode(ViewMode newMode)
{
    m_mode = newMode;
}


}
