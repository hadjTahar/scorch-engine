#ifndef TIMERCALLBACK_H
#define TIMERCALLBACK_H


#include "timerbase.h"


namespace Qx::prv
{

class TimerSingleshot;

class TimerCallback : public prv::TimerBase
{
    friend class GraphicsApp;

public:
    TimerCallback();
    void start(x_count loopCount , x_time msDur );
    void stop();

    /// ## This returns a pointer valid
    /// ## for one use only, DO NOT capture it
    /// ## or store it.
    ///
    static TimerSingleshot &singleShot(const x_time msDur );


    x_time duration() const;
    prv::x_timerCallback timeout;

protected:
    void step(x_time fixDltTicks) override;
    void removeSingshot( TimerCallback *tmr );
    static void clearSingleShots();


private:
    x_count m_counter;
    x_count m_loopCount;
    x_time  m_nextClick;
    x_time  m_duration;
    bool    m_singleShot;


    static std::vector<std::unique_ptr<TimerCallback>> m_singleShots;
};

}

#endif // TIMERCALLBACK_H
