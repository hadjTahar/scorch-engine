#ifndef TIMERLOOP_H
#define TIMERLOOP_H

#include "timerbase.h"


namespace Qx::prv
{

struct DelayLoop
{
    x_count loopsPerFrame;
    x_real  fixedDltMS;
    x_time  delayPerFrameMS;
    x_time  fixedDltTicks;
};

class TimerLoop : public TimerBase
{

public:
    static void init( x_real pps, x_real fpsHint );
    static DelayLoop delayLoop();

private:
    static x_time delayPerFrameMS();

    static void check(const DelayLoop &dltLoop );
private:

    static x_time  m_targetDelay;
    static x_time  m_fixedDltFrame;
    static x_time  m_accumulatedTime;

};

}
#endif // TIMERLOOP_H
