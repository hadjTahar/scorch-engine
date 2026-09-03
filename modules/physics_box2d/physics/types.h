#ifndef TYPES_H
#define TYPES_H

#include <box2d/types.h>
#include <box2d/box2d.h>


namespace Qx::Box2D {
using World = b2WorldId;



/// ## Shapes
///
using Polygon = b2Polygon;
using Circle  = b2Circle;


/// ## Defs / Options
///
struct WorldOpts : b2WorldDef
{
    WorldOpts():
        b2WorldDef( b2DefaultWorldDef() )
    {
    }


};


struct BodyOpts : b2BodyDef
{
    BodyOpts():
        b2BodyDef( b2DefaultBodyDef() )
    {
    }
};


struct ShapeOpts : b2ShapeDef
{
    ShapeOpts():
        b2ShapeDef( b2DefaultShapeDef() )
    {
    }
};

/// ## ID's
///
using Shape = b2ShapeId;



struct Body
{
    friend class PhysicsComponent;

    Body( World world):
        opts{ b2DefaultBodyDef() },
        id{ b2CreateBody(world, &opts) }
    {
    }

    void setPosition( const b2Pos &pos)
    {
        b2Body_SetTransform( id, pos, b2Body_GetRotation( id ) );
    }

    void setLinearVelocity( const b2Pos &vel )
    {
        b2Body_SetLinearVelocity( id, vel );
    }

    void setType( b2BodyType tp )
    {
        b2Body_SetType( id, tp );
    }


private:
    b2BodyId  id;
    b2BodyDef opts;
};


}

#endif // TYPES_H
