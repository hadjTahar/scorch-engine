#include "graphicsitem3d.h"

#include "graphicsscene.h"

namespace Qx::prv
{

GraphicsItem3D::GraphicsItem3D(CoreItem *parent):
    prv::GraphicsItem{ parent },
    m_graphicsModel{ make_unique_meta<GraphicsModel>() }
{
    m_itemType = ItemType::GraphicsItem3D;
    transform.setSize( {10,10,10 });
}


void GraphicsItem3D::render(Canvas *)
{
    /// ## This sdhould never be called
    /// ## Always assert this if it get called
    dbg_assert( false )<< "Can't call ::render(Canvas) for 3D item";
}

GraphicsModel *GraphicsItem3D::graphicsModel() const
{
    return m_graphicsModel.get();
}


}
