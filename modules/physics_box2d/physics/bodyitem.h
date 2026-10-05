#ifndef BODYITEM_H
#define BODYITEM_H

#include <items/rectangle.h>
#include "physicsproperties.h"

struct b2Polygon;

namespace Qx::Box2D {


class Body;

class BodyItem : public Rectangle
{
    QX_META_OBJECT( "Qx::Box2D::BodyItem",
                   prv::MetaItemType::PhysicsItem2D,
                   prv::MetaItemType::PhysicsItem2D )

    friend class WorldItem;
    friend class PhysicsProperties;

public:
    BodyItem(CoreItem *parent);



    /// ## Functions
    /// ## ----------------------------------------------------

    b2Polygon makeBox(float width, float height);


private:
    using Rectangle::transform;

public:
    Body *m_body;


public:
    PhysicsProperties physics;
};

}

#endif // BODYITEM_H
