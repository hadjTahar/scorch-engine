#include "shape.h"
#include "body.h"

#include <box2d/box2d.h>

namespace Qx::Box2D {



Shape::Shape(private_ctor_t,
             const Body &body,
             const Polygon &polygon)
{
    auto shapeOpts  = b2DefaultShapeDef();
    m_shapeId       = b2CreatePolygonShape( body.m_id, &shapeOpts, &polygon );
}

Shape::Shape(private_ctor_t,
             const Body &body,
             const Qx::Box2D::Circle &circle )
{
    auto shapeOpts  = b2DefaultShapeDef();
    m_shapeId       = b2CreateCircleShape( body.m_id, &shapeOpts, &circle );
}


void Shape::setShapeDensity(float density, bool updateBodyMass)
{
    b2Shape_SetDensity( m_shapeId, density, updateBodyMass );
}

}