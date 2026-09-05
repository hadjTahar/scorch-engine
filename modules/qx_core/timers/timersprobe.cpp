#include "timersprobe.h"
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <misc/platfrom.h>



namespace Qx::prv {

x_time    TimersProbe::m_startFrame     = 0;
Parameter TimersProbe::m_frameRate      = {9999, 0, 0, 0, 0};
Parameter TimersProbe::m_loopsPerFrame  = {9999, 0, 0, 0, 0};
Parameter TimersProbe::m_delayPerFrame  = {9999, 0, 0, 0, 0};
Parameter TimersProbe::m_ramUsage       = {9999, 0, 0, 0, 0};

void TimersProbe::startProbe()
{
    if constexpr( !QX_DEF_ENABLE_FPS_PROBE )
        return;
    m_startFrame = SDL_GetTicks();
}

void TimersProbe::endProbe(int loopsPerFrame, x_time delayPerFrame)
{
    if constexpr( !QX_DEF_ENABLE_FPS_PROBE )
        return;
    const auto cur = SDL_GetTicks();
    const auto dlt = cur - m_startFrame;
    m_frameRate.add( 1000.f / dlt );
    m_loopsPerFrame.add( loopsPerFrame );
    m_delayPerFrame.add( delayPerFrame );
    m_ramUsage.add( Platfrom::ramUsage() );

    if( (m_delayPerFrame.cnt % 20) != 0 )
        return;
    // m_frameRate.disp( "FPS" );
    // m_loopsPerFrame.disp( "Loops" );
    // m_delayPerFrame.disp( "Delay" );
    // m_ramUsage.disp( "RAM" );

}

void TimersProbe::disp(SDL_Window *win)
{
    if constexpr( !QX_DEF_ENABLE_FPS_PROBE )
        return;

    const x_string ramUsage = "RAM(" + std::to_string( Platfrom::ramUsage() ) + ")";

    const auto str = m_frameRate.disp( "FPS" ) + " , " +
                     m_loopsPerFrame.disp( "Loops per frame" ) + " , " +
                     m_delayPerFrame.disp( "Delay per frame" ) + " , " +
                     m_ramUsage.disp( "RAM" );
    SDL_SetWindowTitle( win,  str.data() );
}


}
