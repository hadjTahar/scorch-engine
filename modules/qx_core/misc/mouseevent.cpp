#include "mouseevent.h"


namespace Qx{

MouseEvent::MouseEvent(const x_vector3 &winPos,
                       const x_vector3 &itmPos,
                       const x_vector2 &wheel,
                       uint8_t btn,
                       uint8_t clks):
    Event{},
    m_windowPos{ winPos },
    m_itemPos{ itmPos },
    m_wheel{ wheel },
    m_clicks{ clks },
    m_button{ static_cast<MouseButton>( btn ) },
    m_eventType{ MouseEventType::MouseNone }
{
}

MouseEvent::~MouseEvent()
{
}

MouseEvent MouseEvent::operator=(const MouseEvent &rhs)
{
    m_windowPos = rhs.m_windowPos;
    m_itemPos   = rhs.m_itemPos;
    m_wheel     = rhs.m_wheel;
    m_clicks    = rhs.m_clicks;
    m_button    = rhs.m_button;
    m_eventType = rhs.m_eventType;
    // m_depth         = rhs.m_depth;
    // m_renderableID  = rhs.m_renderableID;
    // m_valid         = rhs.m_valid;
    return *this;
}




uint8_t MouseEvent::clicks() const
{
    return m_clicks;
}

x_vector3 MouseEvent::windowPos() const
{
    return m_windowPos;
}

x_vector3 MouseEvent::itemPos() const
{
    return m_itemPos;
}

x_vector2 MouseEvent::wheel() const
{
    return m_wheel;
}

MouseButton MouseEvent::button() const
{
    return m_button;
}

MouseEventType MouseEvent::eventType() const
{
    return m_eventType;
}


}
