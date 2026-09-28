#include "bodyitem.h"
#include <box2dcpp/body.h>


namespace Qx::Box2D {

BodyItem::BodyItem(CoreItem *parent):
    Rectangle{ parent },
    physics{this},
    m_body{ nullptr }
{
}



}

