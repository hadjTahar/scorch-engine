#include "lineareasing.h"

namespace Qx
{

LinearEasing::LinearEasing()
{
}

x_real LinearEasing::updateValue(x_real msDelta)
{
    if( m_done )
        return m_property;
    const auto t = stepTime( msDelta );
    if( m_done )
        m_property = value;
    else
        m_property = t * value;
    return m_property;
}

}
