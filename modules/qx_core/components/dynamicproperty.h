#ifndef DYNAMICPROPERTY_H
#define DYNAMICPROPERTY_H

#include "corecomponent.h"


namespace Qx
{

template<typename EasingType>
class DynamicProperty : public prv::CoreComponent
{
public:
    DynamicProperty(prv::GraphicsItem *parentItem):
        CoreComponent{ parentItem },
        value{ m_easing.value },
        reset{ false },
        process{ CoreComponent::process },
        m_resetOffset{ 0 },
        m_property{ m_easing.m_property },
        m_done{ m_easing.m_done },
        m_running{ false }
    {
        process = [this](x_real msDelta)
        {
            if( progress )
            {
                m_running = !m_done && (m_property !=value);
                if( m_running ){
                    auto storedValue = value;
                    value = reset? value : (storedValue-m_resetOffset);
                    const auto res = m_resetOffset + m_easing.updateValue( msDelta );
                    value = storedValue;
                    progress( res, m_done );
                }
                if( m_done){
                    m_running = false;
                    m_done = false;
                    m_resetOffset = reset? 0 : value;
                    if( reset )
                    {
                        m_property = 0;
                        value = 0;
                    }
                    else
                        m_property = value;
                    done();


                }
            }
        };
    }

    EasingType * const easing()
    {
        return &m_easing;
    }



public:
    prv::x_progressCallback progress;
    x_real             &value;
    bool                reset;



protected:
    virtual void done(){}

protected:
    /// ## prevent from changing ::process
    prv::x_processCallback &process;
    EasingType m_easing;

private:
    x_real   m_resetOffset;
    x_real  &m_property;
    bool    &m_done;
    bool     m_running;
};

}

#endif // DYNAMICPROPERTY_H
