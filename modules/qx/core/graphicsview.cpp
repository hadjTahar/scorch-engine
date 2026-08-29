#include "graphicsview.h"
#include "graphicswindow.h"

#include "graphicsitem2d.h"
#include "graphicsitem3d.h"
#include "graphicsscene.h"

#include <utils/EntityManager.h>

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

x_matrix4x4 GraphicsView::transform()
{
    return m_transform;
}



}
