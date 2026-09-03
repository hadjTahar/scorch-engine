#ifndef WORLD_H
#define WORLD_H

#include "body.h"
#include "types.h"

#include <vector>

namespace Qx::Box2D {



class World
{

    friend class PhysicsComponent;
    friend class Body;

    struct private_ctor_t {};


public:
    World( private_ctor_t);

public:
    ~World();
    Body *addBody();
    void setGravity( const b2Vec2 &vec);

private:

    b2WorldId   m_id;
    std::vector<Body> m_bodies;

};
}


#endif // WORLD_H
