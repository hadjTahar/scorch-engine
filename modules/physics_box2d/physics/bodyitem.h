#ifndef BODYITEM_H
#define BODYITEM_H

#include "physicsproperties.h"
#include <items/rectangle.h>


namespace Qx::Box2D {


class Body;
class Shape;

class BodyItem : public Rectangle
{
    QX_META_OBJECT( "Qx::Box2D::BodyItem",
                   prv::MetaItemType::PhysicsItem2D,
                   prv::MetaItemType::PhysicsItem2D )

    friend class WorldItem;
    friend class PhysicsProperties;

public:
    BodyItem(CoreItem *parent);


    Shape *addBoxShape( x_real width, x_real height );
    Shape *addCircleShape( x_real rad );

    void setType(BodyType tp );
    BodyType type() const;


    void setLinearVelocity( const b2Pos &vel );
    b2Pos linearVelocity() const;




public:
    PhysicsProperties physics;

private:
    using Rectangle::transform;
    Body *m_body;


};

}

#endif // BODYITEM_H
