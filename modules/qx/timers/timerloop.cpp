#include "timerloop.h"
#include <misc/debugprint.h>


namespace Qx::prv

{

x_time TimerLoop::m_fixedDltFrame    = 0;
x_time TimerLoop::m_targetDelay      = 0;
x_time TimerLoop::m_accumulatedTime  = 0;



void TimerLoop::init(x_real pps, x_real fpsHint)
{
    m_targetDelay       = toTicks(1000.f / fpsHint);
    m_accumulatedTime   = 0;
    m_fixedDltFrame     = toTicks(1000.f / pps);
}


DelayLoop TimerLoop::delayLoop()
{
    // Optional: clamp dt to avoid spiral of death
    const auto dt = std::min(deltaFrame(), toTicks( 30) );
    m_accumulatedTime += dt;
    auto cnt = m_accumulatedTime / m_fixedDltFrame;
    // m_accumulatedTime = std::fmod(m_accumulatedTime, m_fixedDltFrame);
    m_accumulatedTime = m_accumulatedTime % m_fixedDltFrame;

    const auto ret = DelayLoop{static_cast<x_count>( cnt ),
            static_cast<x_real>( toMs( m_fixedDltFrame ) ),
            delayPerFrameMS(),
            m_fixedDltFrame
    };
    check( ret );
    return ret;
}

x_time TimerLoop::delayPerFrameMS()
{
    const auto dltUpdt = deltaUpdates();

    if( dltUpdt > m_targetDelay ){
        dbg_warning_st() << "Loop is taking too much time";
        return 0;
    }
    const auto dlt = static_cast<x_real>(dltUpdt);
    const auto ret = m_targetDelay - dlt;
    return toMs(ret);
}

void TimerLoop::check( const DelayLoop &dltLoop)
{

    if( dltLoop.delayPerFrameMS < 5 )
        dbg_warning_st() << "Delay time per frame is too low: " << dltLoop.delayPerFrameMS;


    // const x_real pps = 1000.f / m_fixedDltFrame;
    // const x_real ratio = pps / m_fpsHint;
    // // dbg_print() << ratio;

    // if( m_accumulatedTime < 0 )
    //     dbg_warning() << "Accumulator went negative. Check timer or update loop logic" ;
    // if( static_cast<int>(dltLoop) > 3*static_cast<int>(ratio) )
    //     dbg_warning() <<
    //         "Too much accumulated delta time between frames,"
    //         " Eg: (60,30) ratio should be around 2" << " : " <<
    //         "pps/fps hint: "   << ratio << " : " <<
    //         "pps/fps actual: " << dltLoop;
}




}
