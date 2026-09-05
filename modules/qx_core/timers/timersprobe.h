#ifndef TIMERSPROBE_H
#define TIMERSPROBE_H


#include <misc/defs.h>
#include <misc/debugprint.h>


#include <iomanip>  // Required for setprecision and fixed

struct SDL_Window;

namespace Qx::prv
{

struct Parameter;


class TimersProbe
{

public:
    static void startProbe();
    static void endProbe( int loopsPerFrame, x_time delayPerFrame );
    static void disp( SDL_Window *win);

private:
    static x_time    m_startFrame;
    static Parameter m_frameRate;
    static Parameter m_loopsPerFrame;
    static Parameter m_delayPerFrame;

    static Parameter m_ramUsage;

};


struct Parameter
{
    x_real min;
    x_real max;
    x_real avg;
    x_real cur;

    x_count  cnt;

    void add( x_real val )
    {
        cnt++;
        if( val < min )
            min = val;
        if( val > max )
            max = val;
        avg += (val - avg) / cnt;

        /// ## A quick way to reset the average
        // if( static_cast<int>(cur) == static_cast<int>(min)  )
        //     avg = cur;
        cur = val;
    }


    std::string disp( const std::string &name)
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(4);

        stream <<
            name << " (" <<
            static_cast<int>(min) << "," <<
            static_cast<int>(max) << "," <<
            static_cast<int>(avg) << "," <<
            static_cast<int>(cur) << ")"
            ;

        return stream.str();
    }


};

}

#endif // TIMERSPROBE_H
