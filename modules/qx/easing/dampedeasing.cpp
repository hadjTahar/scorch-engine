#include "dampedeasing.h"
#include <cmath>

namespace Qx
{



DampedEasing::DampedEasing()
{
    initSettlingTime( 12.7, 100 );
    // initPeakTime( 2.5, 700 );
    // init( 1, .32, 0 );
    // setAccuracy( Accuracy::MidAccuracy );
}


void DampedEasing::init(x_real f, x_real z, x_real r, x_real gn, Accuracy accuracy)
{
    setAccuracy( accuracy );
    const auto   pi_f = pi * f;
    const auto   pi_f_2 = 2 * pi * f;

    m_k1 = z / pi_f;
    m_k2 = 1.0f / ( pi_f_2 * pi_f_2 );
    m_k3 = r * z / pi_f_2;


    m_previousInput = 0;
    m_property = 0;
    m_propertyDrv = 0;
    m_gain = gn;
}

void DampedEasing::initPeakTime(x_real overShoot,
                              x_real peakTime,
                              Accuracy accuracy)
{
    /// ## https://www.geogebra.org/m/mz8hnquw

    const x_real overShoot_0_1 =  100  * overShoot;
    const x_real peakTime_s    = .001f * peakTime;

    const x_real z = computeZeta( 100*overShoot_0_1 );
    const x_real Wd = pi / peakTime_s;
    const x_real w = Wd / ( std::sqrt( 1 - z*z ) );
    const x_real f = w / (2*pi );
    init( f, z, 0.0, 1, accuracy );
}

void DampedEasing::initSettlingTime(x_real overShoot,
                                  x_real settlingTime,
                                  Accuracy accuracy)
{
    /// ## https://www.geogebra.org/m/mz8hnquw

    const x_real overShoot_0_1  =  100  * overShoot;
    const x_real settlingTime_s = .001f * settlingTime;
    const x_real z = computeZeta( overShoot_0_1 );
    const x_real w = 4.0f / ( z * settlingTime_s );
    const x_real f = w / (2*pi );
    init( f, z, 0.0f, 1, accuracy );
}

x_real DampedEasing::updateValue(x_real msDelta)
{
    if( m_done )
        return m_property;

    const x_real secdDelta = .001f * msDelta;
    const x_real gainInput = m_gain * value;
    const x_real err = m_property - gainInput;
    const bool done = std::abs( m_propertyDrv ) < m_tolerance && std::abs( err ) < m_tolerance;
    if( done  ){
        m_done = true;
        m_property = gainInput;
    }
    else{
        const x_real inputDrv = (gainInput - m_previousInput) / secdDelta;
        m_previousInput = gainInput;

        const x_real k2Tmp = static_cast<x_real>(1.1) *
                             ( secdDelta*secdDelta/ 4.f + secdDelta*m_k1/2 );
        const x_real k2Stable = std::max( m_k2, k2Tmp  );

        m_property = m_property + secdDelta * m_propertyDrv;
        m_propertyDrv = m_propertyDrv +
                        secdDelta * ( gainInput + m_k3 * inputDrv - m_property - m_k1 * m_propertyDrv ) / k2Stable;
    }

    return m_property;
}

// void DampedEasing::resetValues()
// {
//     dbg_print_st() << "RESET";
//     // m_property          = 0;
//     // value               = 0;
//     m_previousInput     = 0;
//     m_propertyDrv       = 0;
// }

x_real DampedEasing::computeZeta(x_real overShoot)
{
    const x_real e = std::exp( 1.f );
    const x_real tanPhi = ( (-pi *std::log( e ) ) /
                           (std::log(overShoot) - std::log( 100.f ) )
                           );
    const x_real phi = std::atan( tanPhi );
    const x_real z = std::cos( phi );
    return z;
}

void DampedEasing::setAccuracy(Accuracy accuracy)
{
    switch ( accuracy ) {
    case Accuracy::LowestAccuracy:
        m_tolerance = static_cast<x_real>(.95);
        break;
    case Accuracy::LowAccuracy:
        m_tolerance = static_cast<x_real>(.1);
        break;
    case Accuracy::MidAccuracy:
        m_tolerance = static_cast<x_real>(.01);
        break;
    case Accuracy::HighAccuracy:
        m_tolerance = static_cast<x_real>(0.01);
        break;
    case Accuracy::HighestAccuracy:
        m_tolerance = static_cast<x_real>(0.0001);
        break;
    default:
        m_tolerance = static_cast<x_real>(.75);
        break;
    }
}


}
