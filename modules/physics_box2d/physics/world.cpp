#include "world.h"
#include <box2d/box2d.h>
#include <misc/debug.h>


namespace Qx::Box2D {

World::World(private_ctor_t)
{
    auto opts = b2DefaultWorldDef();
    m_id      = b2CreateWorld( &opts );
}

World::~World()
{
    for ( const auto &body : m_bodies)
        b2DestroyBody( body.m_id );
    b2DestroyWorld( m_id );
}


Body *World::addBody()
{
    m_bodies.emplace_back( Body::private_ctor_t{}, *this );
    return &m_bodies.back();
}

void World::setGravity(const b2Vec2 &vec)
{
    b2World_SetGravity( m_id, vec );
}



}
