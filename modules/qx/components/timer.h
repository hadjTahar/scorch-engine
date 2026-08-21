#ifndef TIMER_H
#define TIMER_H

#include "corecomponent.h"
#include <timers/timercallback.h>



namespace Qx
{

class Timer : public prv::CoreComponent
{
private:

    std::unique_ptr<prv::TimerCallback> m_timer;


public:
    Timer(prv::GraphicsItem *parentItem);

    void start(x_count loopCount , x_time msDur );
    void stop();

    /// ## This returns a pointer valid
    /// ## for one use only, DO NOT capture it
    /// ## or store it.
    ///
    static void singleShot(const x_time msDur, prv::x_timerCallback clb );



    x_time duration() const;
    prv::x_timerCallback &timeout;
};

}

#endif // TIMER_H
