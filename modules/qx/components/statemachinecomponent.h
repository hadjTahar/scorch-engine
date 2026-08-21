#ifndef STATEMACHINECOMPONENT_H
#define STATEMACHINECOMPONENT_H

#include "corecomponent.h"
#include <boost/sml.hpp>



namespace Qx
{

namespace sml = boost::sml;

template<typename StateMachine>
class StateMachineComponent : public prv::CoreComponent
{
public:
    StateMachineComponent(prv::GraphicsItem *parentItem):
        CoreComponent{ parentItem },
        m_stateMachine{parentItem}
    {
    }


    template<typename EventType>
    void processEvent()
    {
        m_stateMachine.process_event(EventType{});
    }

private:
    boost::sml::sm<StateMachine> m_stateMachine;
};


}

#endif // STATEMACHINECOMPONENT_H
