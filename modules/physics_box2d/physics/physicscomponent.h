#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H


#include <components/corecomponent.h>

#include <box2dcpp/manager.h>

namespace Qx::Box2D {



class PhysicsComponent : public prv::CoreComponent
{
public:
    PhysicsComponent(prv::GraphicsItem *gItem);
    World *createWorld();


public:
    prv::x_simpleCallback step;
    Manager m_manager;


};

}

#endif // PHYSICSCOMPONENT_H
