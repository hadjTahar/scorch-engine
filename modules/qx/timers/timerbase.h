#ifndef TIMERBASE_H
#define TIMERBASE_H

#include <misc/defs.h>
#include <misc/callbacks.h>
#include <core/metaobject.h>

namespace Qx::prv
{



class Application;


class TimerBase : public MetaObject
{
    friend class Application;
    QX_META_OBJECT( TimerBase, MetaItemType::NA, MetaItemType::NA )

protected:
    TimerBase();

public:
    virtual ~TimerBase();
    static void initTimer(x_real fps );


protected:
    static x_time toMs( x_time ticks )   {return (1000 * ticks)/m_frequency;}
    static x_time toTicks( x_time ms )   {return (ms * m_frequency) / 1000;}


    static x_time deltaUpdates();
    static x_time deltaFrame();
    static void   clearTimers();


private:
    static void startFrame();
    static void endUpdates();

    static void  stepTimers(x_time fixDltTicks );
    static void  addTimer( TimerBase *tmr );
    virtual void step(x_time fixDltTicks) = 0;


protected:
    static x_time m_startFrame;
    static x_time m_endUpdates;
    static x_time m_endFrame;
    static x_time m_frequency;

    static std::vector<TimerBase*>  m_timers;

    static std::vector<TimerBase*>  m_addedTimers;
    static std::vector<TimerBase*>  m_removedTimers;

};

}

#endif // TIMERBASE_H
