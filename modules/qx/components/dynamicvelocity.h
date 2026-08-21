#ifndef DYNAMICVELOCITY_H
#define DYNAMICVELOCITY_H

#include "corecomponent.h"
#include <core/graphicsitem.h>


namespace Qx
{

template<typename EasingType>
class DynamicVelocity : public prv::CoreComponent
{
public:
    DynamicVelocity(prv::GraphicsItem *parentItem):
        CoreComponent{ parentItem },
        process{ CoreComponent::process },
        dynamicVelocity{}
    {
        m_easing.value = 1;
        process = [this](x_real msDelta)
        {
            const auto done = (velocity == dynamicVelocity);
            m_easing.value = done? 0 : 1;
            x_real res = 1;
            if( m_easing.property() >= 1 )
                velocity = dynamicVelocity;
            else
                res = m_easing.updateValue( msDelta );

            auto itm = graphicsItem();
            const x_vector3 pos = itm->transform.position();
            velocity = res * dynamicVelocity;
            itm->transform.setPosition( pos + msDelta * velocity );

            dbg_print() << res;
        };
    }

    EasingType * const easing()
    {
        return &m_easing;
    }

public:
    x_vector3 dynamicVelocity;

protected:
    x_vector3 velocity;
    /// ## prevent from changing ::process
    prv::x_processCallback &process;
    EasingType m_easing;

};

}

#endif // DYNAMICVELOCITY_H
