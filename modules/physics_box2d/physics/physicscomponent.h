#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <components/corecomponent.h>
#include "types.h"
#include <box2d/box2d.h>


namespace Qx::Box2D {




class PhysicsComponent : public prv::CoreComponent
{
public:
    PhysicsComponent(prv::GraphicsItem *gItem);

    World createWorld(const WorldOpts &wrldOpts);

    /// ## Functions
    /// ## ----------------------------------------------------

    auto static createBody(World world, const BodyOpts &bodyOpts)
    {
        return b2CreateBody( world, &bodyOpts );
    }


    auto static makeBox(float halfWidth, float halfHeight)
    {
        return b2MakeBox(halfWidth,  halfHeight);
    }

    auto static createPolygonShape(Body body,
                                   const ShapeOpts &shapeOpts,
                                   const Polygon  &polygon)
    {
        return b2CreatePolygonShape( body.id, &shapeOpts, &polygon );
    }

    auto static createCircleShape(Body body,
                                   const ShapeOpts &shapeOpts,
                                   const Circle  &circle)
    {
        return b2CreateCircleShape( body.id, &shapeOpts, &circle );
    }


public:
    prv::x_simpleCallback step;

protected:

    std::vector<World> m_worlds;
    // World m_world;

};

}

#endif // PHYSICSCOMPONENT_H
