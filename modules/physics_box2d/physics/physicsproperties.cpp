#include "physicsproperties.h"

#include "bodyitem.h"
#include <box2dcpp/body.h>


namespace Qx::Box2D
{


PhysicsProperties::PhysicsProperties(BodyItem *itm):
    m_pixelScale{ 20,20,1},
    m_bodyItem{itm}
{
}

void PhysicsProperties::setPosition(const x_vector3 &pos)
{
    m_bodyItem->transform.setPosition(
        {
            pos.x,
            pos.y,
            pos.z
        }
        );

    updateBodyPhysics();
}

void PhysicsProperties::setSize(const x_size &sz)
{
    m_bodyItem->transform.setSize({
        sz.width,
        sz.height,
        sz.depth
    });
    updateBodyPhysics();
}

Shape *PhysicsProperties::addBoxShape(x_real width, x_real height)
{
    return m_bodyItem->m_body->addShape( makeBox( width, height ) );
}

Shape *PhysicsProperties::addCircleShape(x_real rad)
{
    return m_bodyItem->m_body->addShape( makeCircle( rad ) );
}

void PhysicsProperties::setType(BodyType tp)
{
    m_bodyItem->m_body->setType( tp );
}

BodyType PhysicsProperties::type() const
{
    return m_bodyItem->m_body->type();
}

void PhysicsProperties::setLinearVelocity(const b2Pos &vel)
{
    const auto bx = toBoxPos( {vel.x , vel.y, 0 } );
    m_bodyItem->m_body->setLinearVelocity( {bx.x, bx.y} );
}

b2Pos PhysicsProperties::linearVelocity() const
{
    return m_bodyItem->m_body->linearVelocity();
}

void PhysicsProperties::updateBodyItem()
{
    if( !m_bodyItem )
        return;

    if( !m_bodyItem->m_body )
        return;

    if( m_bodyItem->m_body->type() == Box2D::BodyType::Static )
        return;

    const auto bPos = m_bodyItem->m_body->position();
    const auto pos = fromBoxPos( {bPos.x, bPos.y, 0} );
    m_bodyItem->transform.setPosition(pos);

}


void PhysicsProperties::updateBodyPhysics()
{
    const auto pos  = m_bodyItem->transform.position();
    const auto bPos = toBoxPos(pos);
    m_bodyItem->m_body->setPosition( {bPos.x, bPos.y} );

}

x_vector3 PhysicsProperties::fromBoxPos(const x_vector3 &bPos)
{
    const auto pos = m_bodyItem->transform.position();
    const auto sz  = m_bodyItem->transform.size();


    return {
            m_pixelScale.x * bPos.x  - .5f * sz.width,
            m_pixelScale.y * bPos.y  - .5f * sz.height,
            pos.z
        };
}

x_vector3 PhysicsProperties::toBoxPos(const x_vector3 &pos)
{
    const auto sz  = m_bodyItem->transform.size();

    return{
        (pos.x  + .5f * sz.width)  / m_pixelScale.x,
        (pos.y  + .5f * sz.height) / m_pixelScale.y,
        (pos.z  + .5f * sz.depth)  / m_pixelScale.z,
    };
}

x_size PhysicsProperties::toBoxSize(const x_size &sz)
{
    return {
        sz.width  / m_pixelScale.x,
        sz.height / m_pixelScale.y,
        sz.depth  / m_pixelScale.z,
    };
}

Polygon PhysicsProperties::makeBox(x_real width, x_real height)
{
    const auto bx = toBoxSize( {.5f*width , .5f*height, 0 } );
    return b2MakeBox(bx.width,  bx.height);
}

Circle PhysicsProperties::makeCircle(x_real rad)
{
    const auto bx = toBoxSize( {rad , rad, rad } );

    Qx::Box2D::Circle circle;
    circle.center = {0, 0};
    circle.radius = bx.width;
    return circle;
}

}
