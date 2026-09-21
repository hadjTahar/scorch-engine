#include "bodyitem.h"


namespace Qx::Box2D {

BodyItem::BodyItem(CoreItem *parent):
    Qx::Rectangle{ parent },
    physics{this},
    m_body{ nullptr }
{
}


}

