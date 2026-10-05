#ifndef PHYSICSPROPERTIES_H
#define PHYSICSPROPERTIES_H

#include <misc/vecs.h>

namespace Qx::Box2D
{

class BodyItem;


class PhysicsProperties
{

public:
    PhysicsProperties(BodyItem *itm);
    void setPosition( const x_vector3 &pos );
    void setSize( const x_size &sz );



    void updateGeometry();

    x_vector3 fromBoxPos(const x_vector3 &bPos );
    x_vector3   toBoxPos(const x_vector3 &pos );

    x_size toBoxSize(const x_size &sz );


protected:
    void updatePhysics();

protected:
    x_vector3  m_pixelScale;
    BodyItem  *m_bodyItem;

};








}


#endif // PHYSICSPROPERTIES_H
