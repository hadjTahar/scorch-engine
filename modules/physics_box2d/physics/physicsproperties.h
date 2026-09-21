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

protected:
    x_vector3  m_pixelScale;
    BodyItem  *m_bodyItem;

};








}


#endif // PHYSICSPROPERTIES_H
