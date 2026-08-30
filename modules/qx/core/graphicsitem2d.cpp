#include "graphicsitem2d.h"

#include "graphicsscene.h"

namespace Qx::prv
{

GraphicsItem2D::GraphicsItem2D(CoreItem *parent):
    prv::GraphicsItem{ parent }
{
    m_itemType = ItemType::GraphicsItem2D;
}

FlexStyle *GraphicsItem2D::flexStyle()
{
    if( m_flexStyle )
        return m_flexStyle.get();

    m_flexStyle = MetaObject::make_unique_meta<FlexStyle>();
    return m_flexStyle.get();
}

void GraphicsItem2D::updateModel(GraphicsModel *)
{
    dbg_assert( false )<< "Can't call ::updateModel for 2D item";
}


}
