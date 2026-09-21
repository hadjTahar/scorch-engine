
#include "physicsproperties.h"

#include "bodyitem.h"
#include <box2dcpp/body.h>


namespace Qx::Box2D
{


PhysicsProperties::PhysicsProperties(BodyItem *itm):
    m_pixelScale{ 1,1,1},
    m_bodyItem{itm}
{
}

void PhysicsProperties::setPosition(const x_vector3 &pos)
{
    m_bodyItem->transform.setPosition(
        {
          m_pixelScale.x * pos.x,
          m_pixelScale.y * pos.y,
          m_pixelScale.z * pos.x}
        );
    m_bodyItem->m_body->setPosition( {pos.x, pos.y } );
}


}
