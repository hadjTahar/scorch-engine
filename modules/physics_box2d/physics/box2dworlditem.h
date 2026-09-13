#ifndef BOX2DWORLDITEM_H
#define BOX2DWORLDITEM_H

#include <items/rectangle.h>


namespace Qx::Box2D {

class WorldItem : public Rectangle
{
    QX_META_OBJECT( "Box2DWorldItem",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::GraphicsItem2D )

public:
    WorldItem(CoreItem *parent);


private:
    x_matrix4x4 m_prevMat;
};

}

#endif // BOX2DWORLDITEM_H
