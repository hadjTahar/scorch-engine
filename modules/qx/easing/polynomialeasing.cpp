#include "polynomialeasing.h"

namespace Qx
{




PolynomialEasing::PolynomialEasing()
{

}

x_real PolynomialEasing::updateValue(x_real msDelta)
{
    const auto t = stepTime( msDelta );
    if( m_done )
        m_property = value;
    else
    {
        const auto res = polynomial? polynomial( t ) : t;
        m_property = res * value;
    }
    return m_property;


}

}
