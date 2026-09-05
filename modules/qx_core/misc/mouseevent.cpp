#include "mouseevent.h"


namespace Qx{

MouseEvent::MouseEvent(x_real xx,
                       x_real yy,
                       uint8_t btn,
                       uint8_t clks,
                       x_real wXX,
                       x_real wYY):
    Event{},
    m_eventType{ MouseEventType::MouseNone },
    m_x{ xx },
    m_y{ yy },
    m_button{ static_cast<MouseButton>( btn ) },
    m_clicks{ clks },
    m_wheelX{ xx },
    m_wheelY{ yy }
{
}

MouseEvent::~MouseEvent()
{
}

MouseEvent MouseEvent::operator=(const MouseEvent &rhs)
{
    m_eventType     = rhs.m_eventType;
    m_x             = rhs.m_x;
    m_y             = rhs.m_y;
    m_button        = rhs.m_button;
    m_clicks        = rhs.m_clicks;
    // m_depth         = rhs.m_depth;
    // m_renderableID  = rhs.m_renderableID;
    // m_valid         = rhs.m_valid;
    return *this;
}

x_real MouseEvent::x() const
{
    return m_x;
}

x_real MouseEvent::y() const
{
    return m_y;
}


uint8_t MouseEvent::clicks() const
{
    return m_clicks;
}

x_real MouseEvent::wheelX() const
{
    return m_wheelX;
}

x_real MouseEvent::wheelY() const
{
    return m_wheelY;
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
