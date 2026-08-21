#include "mousecomponent.h"
#include <core/windowitem.h>

namespace Qx
{

MouseComponent::MouseComponent(prv::GraphicsItem *parentItem):
    EventComponent{ parentItem },
    m_entered{ false }
{
    windowItem()->addMouseComponent( this );
}

MouseComponent::~MouseComponent()
{
    windowItem()->remMouseComponent( this );
}


}
