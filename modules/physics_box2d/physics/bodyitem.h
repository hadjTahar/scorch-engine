#ifndef BODYITEM_H
#define BODYITEM_H

#include "physicsproperties.h"
#include <items/rectangle.h>
#include <box2dcpp/types.h>


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

    Polygon makeBox(x_real width, x_real height);
    Circle makeCircle(x_real rad);


private:
    using Rectangle::transform;

public:
    Body *m_body;


public:
    PhysicsProperties physics;
};

}

#endif // BODYITEM_H
