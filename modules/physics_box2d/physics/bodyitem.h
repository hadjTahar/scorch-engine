#ifndef BODYITEM_H
#define BODYITEM_H

#include "physicsproperties.h"
#include <items/rectangle.h>


namespace Qx::Box2D {


class BodyItem : public Rectangle
{
    QX_META_OBJECT( "Qx::Box2D::BodyItem",
                   prv::MetaItemType::PhysicsItem2D,
                   prv::MetaItemType::PhysicsItem2D )

    friend class WorldItem;
    friend class PhysicsProperties;

public:
    BodyItem(CoreItem *parent);

public:
    PhysicsProperties physics;

private:
    using Rectangle::transform;
    /// ## Populated by WorldItem
    Body *m_body;


};

}

#endif // BODYITEM_H
