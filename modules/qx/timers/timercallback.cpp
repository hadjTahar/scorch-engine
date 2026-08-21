#include "timercallback.h"

#include "timersingleshot.h"


namespace Qx::prv
{


std::vector<std::unique_ptr<TimerCallback>> TimerCallback::m_singleShots = {};

TimerCallback::TimerCallback():
    prv::TimerBase{},
    m_counter{ std::numeric_limits<int>::max() },
    m_loopCount{ 0 },
    m_nextClick{ 0 },
    m_duration{ toTicks( 100 ) },
    m_singleShot{ false }
{
    stop();
}

void TimerCallback::start(x_count loopCount, x_time msDur)
{
    m_duration = toTicks( msDur );
    m_nextClick = m_startFrame + m_duration;
    m_loopCount = loopCount;
    m_counter = 0;
}

void TimerCallback::stop()
{
    m_counter = std::numeric_limits<int>::max();
    /// ## Pevent "m_loopCount == 0"
    m_loopCount = 1;
}

TimerSingleshot &TimerCallback::singleShot(const x_time msDur)
{
    auto tmr = MetaObject::make_unique_meta<TimerSingleshot>();
    auto ret = tmr.get();
    ret->m_singleShot = true;
    ret->start( 1, msDur );
    m_singleShots.push_back( std::move(tmr) );
    return *ret;
}

x_time TimerCallback::duration() const
{
    return m_duration;
}



void TimerCallback::step(x_time fixDltTicks)
{
    dbg_unused( fixDltTicks );
    const auto shouldStep = m_loopCount == 0 ||
                            m_counter < m_loopCount;
    if( !shouldStep )
        return;

    if( m_startFrame > m_nextClick )
    {
        if( timeout )
            timeout();

        if( m_singleShot )
            removeSingshot( this );
        ++m_counter;
        m_nextClick += m_duration;
    }
}

void TimerCallback::removeSingshot(TimerCallback *tmr)
{
    auto it = std::find_if(m_singleShots.begin(),
                           m_singleShots.end(),
                           [tmr](const std::unique_ptr<TimerCallback>& itm)
                           {
                               return itm.get() == tmr;
                           });
    const auto found = it != m_singleShots.end();
    dbg_assert_st( found ) << "Couldn't find single shot timer to remove";
    m_singleShots.erase( it );

    // dbg_print_st() << "ERASED SNGL TMR " << this;
}

void TimerCallback::clearSingleShots()
{
    m_singleShots.clear();
}

}
