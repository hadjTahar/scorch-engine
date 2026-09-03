#include "physicscomponent.h"
#include <box2d/box2d.h>


namespace Qx::Box2D {


PhysicsComponent::PhysicsComponent(prv::GraphicsItem *gItem):
    CoreComponent{ gItem }
{
    process = [this](x_real dlt)
    {
        const auto dltSec = dlt / 1000.0f;
        for ( auto world : m_worlds)
            b2World_Step( world, dltSec, 4);

        if( step )
            step();
    };
}

World PhysicsComponent::createWorld( const WorldOpts &wrldOpts)
{
    const auto ret = b2CreateWorld( &wrldOpts );

    m_worlds.push_back( ret );
    return ret;
}




}
