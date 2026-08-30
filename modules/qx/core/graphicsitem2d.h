#ifndef GRAPHICSITEM2D_H
#define GRAPHICSITEM2D_H

#include "graphicsitem.h"
#include <misc/flexstyle.h>

namespace Qx::prv
{

class GraphicsItem2D : public prv::GraphicsItem
{

    QX_META_OBJECT( "GraphicsItem2D",
                   MetaItemType::GraphicsItem2D,
                   MetaItemType::GraphicsItem2D )

public:
    GraphicsItem2D(CoreItem *parent);
    FlexStyle *flexStyle();



protected:
    void updateModel( GraphicsModel * ) override final;

protected:
    std::unique_ptr<FlexStyle> m_flexStyle;

};

}

#endif // GRAPHICSITEM2D_H
