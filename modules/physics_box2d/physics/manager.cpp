#include "manager.h"
#include <box2d/box2d.h>

namespace Qx::Box2D {



World *Manager::createWorld()
{
    m_worlds.emplace_back( World::private_ctor_t{} );
    return &m_worlds.back();
}

}
