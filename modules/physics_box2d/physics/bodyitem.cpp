#include "bodyitem.h"
#include <box2dcpp/body.h>


namespace Qx::Box2D {

BodyItem::BodyItem(CoreItem *parent):
    Rectangle{ parent },
    physics{this},
    m_body{ nullptr }
{
}

b2Polygon BodyItem::makeBox(float width, float height)
{
    const auto bx = physics.toBoxSize( {.5f*width , .5f*height, 0 } );
    return b2MakeBox(bx.width,  bx.height);
}



}

