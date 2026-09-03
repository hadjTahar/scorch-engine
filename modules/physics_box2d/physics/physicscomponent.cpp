#include "physicscomponent.h"
#include <box2d/box2d.h>


namespace Qx::Box2D {


PhysicsComponent::PhysicsComponent(prv::GraphicsItem *gItem):
    CoreComponent{ gItem }
{
    process = [this](x_real dlt)
    {
        m_manager.step( dlt, 4 );
        if( step )
            step();
    };
}

World *PhysicsComponent::createWorld()
{
    return m_manager.createWorld();
}






}
