#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <misc/defs.h>
#include <misc/flags.h>
#include "event.h"

namespace Qx{

namespace prv{
class GLGraphTree;
class GraphicsWindow;
}


class MouseEvent : public Event
{

    friend class prv::GraphicsWindow;

// protected:
    MouseEvent(x_real  xx,
               x_real  yy,
               uint8_t btn,
               uint8_t clks,
               x_real wXX,
               x_real wYY);
    ~MouseEvent();

public:
    MouseEvent operator=(const MouseEvent & rhs);


    MouseEventType eventType() const;
    x_real x() const;
    x_real y() const;
    MouseButton button() const;
    uint8_t clicks() const;

    x_real wheelX() const;
    x_real wheelY() const;

protected:

    MouseEventType m_eventType;
    x_real       m_x;
    x_real       m_y;
    MouseButton  m_button;
    uint8_t      m_clicks;


    x_real       m_wheelX;
    x_real       m_wheelY;
    // x_real    m_depth;
    // v_count  m_renderableID;
    // bool      m_valid;
};

}

#endif // MOUSEEVENT_H
