#include "bodyitem.h"
#include <box2dcpp/body.h>


namespace Qx::Box2D {

BodyItem::BodyItem(CoreItem *parent):
    Rectangle{ parent },
    physics{this},
    m_body{ nullptr }
{
}

Polygon BodyItem::makeBox(x_real width, x_real height)
{
    const auto bx = physics.toBoxSize( {.5f*width , .5f*height, 0 } );
    return b2MakeBox(bx.width,  bx.height);
}

Circle BodyItem::makeCircle(x_real rad)
{
    const auto bx = physics.toBoxSize( {rad , rad, rad } );


    Qx::Box2D::Circle circle;
    circle.center = {0, 0};
    circle.radius = bx.width;
    return circle;
}



}

