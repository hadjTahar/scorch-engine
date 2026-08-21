#ifndef EVENTCOMPONENT_H
#define EVENTCOMPONENT_H

#include "corecomponent.h"
#include <misc/flags.h>



namespace Qx::prv
{

class WindowItem;
class GraphicsCamera;
class GraphicsScene;

class EventComponent : public prv::CoreComponent
{
public:
    EventComponent(prv::GraphicsItem *parentItem);
    bool checkEvent(const MouseEvent &event, prv::GraphicsScene *scn);

    MousePolicy mousePolicy() const;
    void setMousePolicy(MousePolicy newMousePolicy);

protected:

    MousePolicy m_mousePolicy;
};

}

#endif // EVENTCOMPONENT_H
