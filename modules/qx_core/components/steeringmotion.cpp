#include "steeringmotion.h"

#include <core/graphicsitem.h>

namespace Qx::prv
{

SteeringMotion::SteeringMotion(GraphicsItem *parentItem):
    CoreComponent{ parentItem },
    process{ CoreComponent::process },
    m_done{ false }
{
    const auto speed = 15;
    m_speedEasing.value = speed;
    m_speedEasing.init( 3, .71, 0 );


    process = [this](x_real msDelta)
    {
        if( m_done )
            return;
        m_speedEasing.updateValue( msDelta );
        const x_real vl = m_speedEasing.property();

        const x_vector3 curPos = m_graphicsItem->transform.position();
        const x_vector3 tarPos = x_vector3{ 300, 300, 1 };
        const x_vector3 res = Follow( curPos, tarPos, vl, 33 );
        if( res == x_vector3{} )
            return;


        // Manually update the position based on delta time
        const x_vector3 newPos {
            curPos.x + res.x * msDelta,
            curPos.y + res.y * msDelta,
            curPos.z + res.z * msDelta
        };
        m_graphicsItem->transform.setPosition( newPos );

        // dbg_print() << "-------------------------";
        // dbg_print() << m_graphicsItem;
        // dbg_print() << curPos.x << " : " << curPos.y;
        // dbg_print() << res.x << " : " << res.y;

        m_done = m_speedEasing.done();
    };
}

x_vector3 SteeringMotion::Seek(x_vector3 currentPos, x_vector3 targetPos, float speed)
{
    x_vector3 direction = (targetPos - currentPos);
    direction = x_vector::normalize(direction);
    return direction * speed;
}

x_vector3 SteeringMotion::Follow(x_vector3 currentPos,
                                 x_vector3 targetPos,
                                 float speed,
                                 float stopDistance)
{
    const auto dist = x_vector::distance(targetPos, currentPos);
    if (dist <= stopDistance){
        return x_vector3(0, 0, 0);
    }
    return Seek(currentPos, targetPos, speed);
}


}
