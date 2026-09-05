#ifndef DYNAMICPOSITION_H
#define DYNAMICPOSITION_H

#include "dynamicproperty.h"

#include <core/graphicsitem.h>


namespace Qx
{

template<typename EasingType>
class DynamicPosition : public DynamicProperty<EasingType>
{
public:
    using DynamicProperty<EasingType>::graphicsItem;

public:
    DynamicPosition(prv::GraphicsItem *parentItem):
        DynamicProperty<EasingType>{ parentItem },
        dynamicPosition{},
        progress{ DynamicProperty<EasingType>::progress },
        value{ DynamicProperty<EasingType>::value },
        reset{ DynamicProperty<EasingType>::reset }
    {
        reset = true;
        value = 1;
        progress = [this](Qx::x_real val, bool done)
        {
            auto itm = graphicsItem();
            const x_vector3 pos = itm->transform.position();
            if( dynamicPosition == pos && !done )
                return;
            if( done )
                return;
            itm->transform.setPosition( val * dynamicPosition );

        };
    }

    x_vector3 dynamicPosition;
protected:
    void done() override
    {
        auto itm = graphicsItem();
        itm->transform.setPosition( dynamicPosition );
        value = 1;
    }

protected:
    prv::x_progressCallback &progress;
    x_real                  &value;
    bool                    &reset;
};

}

#endif // DYNAMICPOSITION_H
