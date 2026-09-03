#ifndef BODY_H
#define BODY_H

#include "shape.h"
#include <vector>


namespace Qx::Box2D {

class World;

class Body
{
    friend class PhysicsComponent;
    friend class Shape;
    friend class World;

    struct private_ctor_t {};

public:
    Body( private_ctor_t, const World &world);
    ~Body();

    Shape *addShape( const Polygon &polygon );
    Shape *addShape( const Circle &circle );
    void setPosition( const b2Pos &pos);
    void setLinearVelocity( const b2Pos &vel );
    void setType( b2BodyType tp );



private:
    Body(){}

private:
    b2BodyId  m_id;
    std::vector<Shape> m_shapes;
};

}



#endif // BODY_H
