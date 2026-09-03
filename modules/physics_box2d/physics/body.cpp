#include "body.h"
#include "world.h"
#include <box2d/box2d.h>


namespace Qx::Box2D {

Body::Body(private_ctor_t, const World &world)
{
    auto opts = b2DefaultBodyDef();
    m_id      = b2CreateBody(world.m_id, &opts);
}

Body::~Body()
{
    /// ## b2DestroyBody already destroys
    /// ## Shapes and joints
    // for ( const auto &shp : m_shapes)
    //     b2DestroyShape( shp.m_shapeId, true );
}

Shape *Body::addShape(const Polygon &polygon)
{
    m_shapes.emplace_back( Shape::private_ctor_t{}, *this, polygon );
    return &m_shapes.back();
}

Shape *Body::addShape(const Circle &circle)
{
    m_shapes.emplace_back( Shape::private_ctor_t{}, *this, circle );
    return &m_shapes.back();
}

void Body::setPosition(const b2Pos &pos)
{
    b2Body_SetTransform( m_id, pos, b2Body_GetRotation( m_id ) );
}

void Body::setLinearVelocity(const b2Pos &vel)
{
    b2Body_SetLinearVelocity( m_id, vel );
}

void Body::setType(b2BodyType tp)
{
    b2Body_SetType( m_id, tp );
}

}

