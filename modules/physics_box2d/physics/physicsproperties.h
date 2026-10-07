#ifndef PHYSICSPROPERTIES_H
#define PHYSICSPROPERTIES_H

#include <misc/vecs.h>
#include <box2dcpp/types.h>

namespace Qx::Box2D
{

class BodyItem;
class Body;
class Shape;

class PhysicsProperties
{

    friend class BodyItem;
    friend class WorldItem;

public:
    PhysicsProperties(BodyItem *itm);
    void setPosition( const x_vector3 &pos );
    void setSize( const x_size &sz );


    Shape *addBoxShape( x_real width, x_real height );
    Shape *addCircleShape( x_real rad );

    void setType(BodyType tp );
    BodyType type() const;


    void setLinearVelocity( const b2Pos &vel );
    b2Pos linearVelocity() const;


protected:


    void updateBodyItem();
    void updateBodyPhysics();
    x_vector3 fromBoxPos(const x_vector3 &bPos );
    x_vector3 toBoxPos(const x_vector3 &pos );
    x_size    toBoxSize(const x_size &sz );


    Polygon makeBox(x_real width, x_real height);
    Circle makeCircle(x_real rad);


protected:
    x_vector3  m_pixelScale;
    BodyItem  *m_bodyItem;

};








}


#endif // PHYSICSPROPERTIES_H
