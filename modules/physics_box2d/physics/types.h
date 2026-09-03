#ifndef TYPES_H
#define TYPES_H

#include <box2d/types.h>


namespace Qx::Box2D {



/// ## Shapes
///
using Polygon = b2Polygon;
using Circle  = b2Circle;



/// ## Functions
/// ## ----------------------------------------------------

auto static makeBox(float halfWidth, float halfHeight)
{
    return b2MakeBox(halfWidth,  halfHeight);
}





}

#endif // TYPES_H
