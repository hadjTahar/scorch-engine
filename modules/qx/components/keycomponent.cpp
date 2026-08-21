#include "keycomponent.h"
#include <core/windowitem.h>


namespace Qx
{


KeyComponent::KeyComponent(prv::GraphicsItem *parentItem):
    EventComponent{ parentItem },
    m_focusPolicy{ FocusPolicy::Wheel },
    m_focused{ false }
{
    windowItem()->addKeyComponent( this );
}

KeyComponent::~KeyComponent()
{
    windowItem()->remKeyComponent( this );
}

FocusPolicy KeyComponent::focusPolicy() const
{
    return m_focusPolicy;
}

void KeyComponent::setFocusPolicy(FocusPolicy newFocusPolicy)
{
    m_focusPolicy = newFocusPolicy;
}

bool KeyComponent::focused() const
{
    return m_focused;
}

void KeyComponent::setFocused(bool newFocused)
{
    m_focused = newFocused;
    windowItem()->updateFocusKeyComponent( this, FocusPolicy::User );
}




}
