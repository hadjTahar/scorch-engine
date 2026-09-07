#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <misc/vecs.h>
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
    MouseEvent(const x_vector3 &winPos,
               const x_vector3 &itmPos,
               const x_vector2 &wheel,
               uint8_t btn,
               uint8_t clks);
    ~MouseEvent();

public:
    MouseEvent operator=(const MouseEvent & rhs);


    MouseEventType eventType() const;    
    MouseButton button() const;
    uint8_t clicks() const;



    x_vector3 windowPos() const;

    x_vector3 itemPos() const;

    x_vector2 wheel() const;

protected:


    x_vector3       m_windowPos;
    x_vector3       m_itemPos;
    x_vector2       m_wheel;
    uint8_t         m_clicks;
    MouseButton     m_button;
    MouseEventType  m_eventType;

    // x_real    m_depth;
    // v_count  m_renderableID;
    // bool      m_valid;
};

}

#endif // MOUSEEVENT_H
