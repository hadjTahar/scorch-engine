#ifndef MOUSECOMPONENT_H
#define MOUSECOMPONENT_H

#include "eventcomponent.h"

namespace Qx
{


class MouseComponent : public prv::EventComponent
{
    friend class prv::GraphicsWindow;
public:
    MouseComponent(prv::GraphicsItem *parentItem);
    ~MouseComponent();

public:
    prv::x_clickCallback pressed;
    prv::x_clickCallback released;
    prv::x_clickCallback clicked;
    prv::x_clickCallback move;
    prv::x_clickCallback enter;
    prv::x_clickCallback leave;
    prv::x_clickCallback wheel;

protected:
    bool m_entered;



};

}

#endif // MOUSECOMPONENT_H
