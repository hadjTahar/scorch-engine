#ifndef KEYCOMPONENT_H
#define KEYCOMPONENT_H

#include "eventcomponent.h"
#include <misc/flags.h>


namespace Qx
{

class KeyComponent : public prv::EventComponent
{
public:

    friend class prv::WindowItem;
public:
    KeyComponent(prv::GraphicsItem *parentItem);
    ~KeyComponent();

    FocusPolicy focusPolicy() const;
    void setFocusPolicy(FocusPolicy newFocusPolicy);


public:
    prv::x_keyCallback         keyPressed;
    prv::x_keyCallback         keyReleased;
    prv::x_sequenceCallback sequence;

    bool focused() const;
    void setFocused(bool newFocused);

private:

    FocusPolicy m_focusPolicy;
    bool        m_focused;
};

}

#endif // KEYCOMPONENT_H
