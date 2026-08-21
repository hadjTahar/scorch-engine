#ifndef REACTIVEPROPERTY_H
#define REACTIVEPROPERTY_H

#include "corecomponent.h"


namespace Qx {

template<typename PropertyType>
class ReactiveProperty : public prv::CoreComponent
{
public:
    ReactiveProperty( prv::GraphicsItem *gItem):
        prv::CoreComponent{ gItem }
    {
        process = [this](x_real)
        {
            if( !update )
                return;

            if( m_entity == update() )
                return;

            m_entity = update();
            if( changed )
                changed( m_entity );
        };
    }

    prv::x_callback<PropertyType(void)> update;
    prv::x_callback<void(const PropertyType&)> changed;

protected:
    PropertyType m_entity;
};


}

#endif // REACTIVEPROPERTY_H
