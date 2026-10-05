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

    updatePhysics();
}

void PhysicsProperties::setSize(const x_size &sz)
{
    m_bodyItem->transform.setSize({
        sz.width,
        sz.height,
        sz.depth
    });
    updatePhysics();
}

void PhysicsProperties::updateGeometry()
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


void PhysicsProperties::updatePhysics()
{
    const auto pos  = m_bodyItem->transform.position();
    const auto bPos = toBoxPos(pos);
    m_bodyItem->m_body->setPosition( {bPos.x, bPos.y} );

}

}
