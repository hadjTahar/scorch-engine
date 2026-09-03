#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include <components/corecomponent.h>
#include "body.h"
#include "world.h"

namespace Qx::Box2D {




class PhysicsComponent : public prv::CoreComponent
{
public:
    PhysicsComponent(prv::GraphicsItem *gItem);
    World *createWorld();




public:
    prv::x_simpleCallback step;

protected:

    std::vector<World> m_worlds;
    // World m_world;

};

}

#endif // PHYSICSCOMPONENT_H
