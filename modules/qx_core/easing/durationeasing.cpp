#include "durationeasing.h"

#include <misc/debug.h>

namespace Qx::prv
{

DurationEasing::DurationEasing():
    duration{ 1000 },
    m_t{ 0 }
{
}

x_real DurationEasing::stepTime(x_real msDelta)
{
    m_t += msDelta;

    const x_real t = m_t / duration;
    dbg_assert( msDelta < duration ) <<
        "Delta time is larger than duration (duration) "
        "This is due to either low fps setting, "
        "smallest duration that can be set must be smaller than fps sleep timeout"
        "Or performance loss is caussing a large delta time";

    m_done = (t >= 1.);
    if( m_done ){
        // m_done = false;
        m_t = 0;
        return 1;
    }

    return t;
}

}
