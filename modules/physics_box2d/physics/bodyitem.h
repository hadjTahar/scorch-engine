#ifndef BODYITEM_H
#define BODYITEM_H

#include <items/rectangle.h>

#include "physicsproperties.h"

namespace Qx::Box2D {


class Body;


class BodyItem : public Qx::Rectangle
{
    QX_META_OBJECT( "Qx::Box::BodyItem",
                   prv::MetaItemType::PhysicsItem2D,
                   prv::MetaItemType::PhysicsItem2D )

    friend class WorldItem;
    friend class PhysicsProperties;

public:
    BodyItem(CoreItem *parent);



private:
    Body *m_body;


public:
    PhysicsProperties physics;
};

}

#endif // BODYITEM_H
