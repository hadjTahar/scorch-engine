#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "defs.h"
#include "event.h"

namespace Qx{

namespace prv{
class WindowItem;
}


class KeyEvent : public Event
{


    KeyEvent(x_keycode kCode,
             x_modifiers kMod ,
             bool rpt);
    ~KeyEvent();
public:
    x_keycode   key() const;
    x_modifiers modifiers() const;

    bool repeat() const;

private:
    friend class prv::WindowItem;
    x_keycode    m_key;
    x_modifiers  m_modifiers;
    bool         m_repeat;
};

}
#endif // KEYEVENT_H

