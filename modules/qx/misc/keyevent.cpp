#include "keyevent.h"

namespace Qx{


KeyEvent::KeyEvent(x_keycode kCode,
                   x_modifiers kMod,
                   bool rpt):
    Event{},
    m_key{kCode},
    m_modifiers{kMod},
    m_repeat{ rpt }
{

}

KeyEvent::~KeyEvent()
{
}

x_keycode KeyEvent::key() const
{
    return m_key;
}

x_modifiers KeyEvent::modifiers() const
{
    return m_modifiers;
}

bool KeyEvent::repeat() const
{
    return m_repeat;
}



}
