#include "physicscomponent.h"
#include <box2d/box2d.h>


namespace Qx::Box2D {


PhysicsComponent::PhysicsComponent(prv::GraphicsItem *gItem):
    CoreComponent{ gItem }
{
    process = [this](x_real dlt)
    {
        const auto dltSec = dlt / 1000.0f;
        for ( auto &world : m_manager.m_worlds)
            b2World_Step( world.m_id, dltSec, 4);

        if( step )
            step();
    };
}

World *PhysicsComponent::createWorld()
{
   return m_manager.createWorld();
}






}
