#include "graphicsitem3d.h"

#include "graphicsscene.h"

namespace Qx::prv
{

GraphicsItem3D::GraphicsItem3D(CoreItem *parent):
    prv::GraphicsItem{ parent }
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

GraphicsMeshModel *GraphicsItem3D::graphicsMeshModel() const
{
    auto ret = m_graphicsMeshModel.get();
    dbg_assert( ret )<< "m_graphicsMeshModel is null";
    return ret;
}


}
