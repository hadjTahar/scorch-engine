#include "timerbase.h"
#include <SDL3/SDL_timer.h>

namespace Qx::prv
{


x_time TimerBase::m_startFrame  = 0;
x_time TimerBase::m_endUpdates  = 100;
x_time TimerBase::m_endFrame    = m_startFrame;
x_time TimerBase::m_frequency   = 100;


std::vector<TimerBase*> TimerBase::m_timers         = {};
std::vector<TimerBase*> TimerBase::m_addedTimers    = {};
std::vector<TimerBase*> TimerBase::m_removedTimers  = {};


TimerBase::TimerBase()
{
    m_addedTimers.push_back( this );
}

void TimerBase::initTimer(x_real fps)
{
    m_frequency  = SDL_GetPerformanceFrequency();

    m_endFrame   = SDL_GetPerformanceCounter();
    m_startFrame = m_endFrame;
    m_endUpdates = m_endFrame;
    startFrame();
}


x_time TimerBase::deltaUpdates()
{
    dbg_assert_st( m_endUpdates > m_startFrame ) <<
        "m_endUpdates must be greater than m_startFrame";

    return m_endUpdates - m_endFrame;
}

x_time TimerBase::deltaFrame()
{
    dbg_assert_st( m_endFrame >= m_startFrame ) <<
        "m_endFrame must be greater than m_startFrame";
    return m_endFrame - m_startFrame;
}

void TimerBase::clearTimers()
{
    TimerBase::stepTimers( 0 );
    dbg_assert_st( TimerBase::m_timers.empty()  ) <<
        "TimerBase::m_timers should be empty";
}

TimerBase::~TimerBase()
{    
    m_removedTimers.push_back( this );
}


void TimerBase::startFrame()
{
    m_startFrame  = m_endFrame;
    m_endFrame    = SDL_GetPerformanceCounter();
}


void TimerBase::endUpdates()
{
    m_endUpdates = SDL_GetPerformanceCounter();
}

void TimerBase::stepTimers(x_time fixDltTicks)
{
    for ( auto tmr : m_removedTimers)
    {
        auto it = std::find_if(m_timers.begin(),
                               m_timers.end(),
                               [tmr](TimerBase *itm)
                               {
                                   return itm == tmr;
                               });
        const auto found = it != m_timers.end();
        dbg_assert_st( found ) << "Couldn't find timer to remove";
        m_timers.erase( it );
    }

    for ( auto tmr : m_addedTimers)
        m_timers.push_back( tmr );

    m_removedTimers.clear();
    m_addedTimers.clear();

    for ( auto tmr : m_timers){
        MetaObject::check_is_alive( tmr );
        tmr->step( fixDltTicks);
    }
}




}
