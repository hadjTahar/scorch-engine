#include "bodyitem.h"
#include <box2dcpp/body.h>


namespace Qx::Box2D {

BodyItem::BodyItem(CoreItem *parent):
    Rectangle{ parent },
    physics{this},
    m_body{ nullptr }
{
}

Shape *BodyItem::addBoxShape(x_real width, x_real height)
{
    return m_body->addShape( physics.makeBox( width, height ) );
}

Shape *BodyItem::addCircleShape(x_real rad)
{
    return m_body->addShape( physics.makeCircle( rad ) );
}


void BodyItem::setType(BodyType tp)
{
    m_body->setType( tp );
}

BodyType BodyItem::type() const
{
    return m_body->type();
}

void BodyItem::setLinearVelocity(const b2Pos &vel)
{
    const auto bx = physics.toBoxPos( {vel.x , vel.y, 0 } );
    m_body->setLinearVelocity( {bx.x, bx.y} );
}

b2Pos BodyItem::linearVelocity() const
{
    return m_body->linearVelocity();
}


}

