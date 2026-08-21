#include "timer.h"

#include <timers/timersingleshot.h>
#include <functional>

namespace Qx
{


Timer::Timer(prv::GraphicsItem *parentItem):
    CoreComponent{ parentItem },
    m_timer{ MetaObject::make_unique_meta<prv::TimerCallback>() },
    timeout{ m_timer->timeout }
{
}

void Timer::start(x_count loopCount, x_time msDur)
{
    m_timer->start( loopCount, msDur );
}

void Timer::stop()
{
    m_timer->stop();
}

x_time Timer::duration() const
{
    return m_timer->duration();
}

void Timer::singleShot(const x_time msDur, prv::x_timerCallback clb)
{
    prv::TimerCallback::singleShot( msDur ).timeout = clb;
}

// prv::TimerCallback * const Timer::timer()
// {
//     return m_timer.get();
// }

}

