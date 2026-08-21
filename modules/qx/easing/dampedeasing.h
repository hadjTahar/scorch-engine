#ifndef DAMPEDEASING_H
#define DAMPEDEASING_H

#include "propertyeasing.h"




namespace Qx
{

class DampedEasing : public prv::PropertyEasing
{
    enum class Accuracy{
        LowestAccuracy,
        LowAccuracy,
        MidAccuracy,
        HighAccuracy,
        HighestAccuracy
    };


public:
    DampedEasing();
    /// ## f : Natural Frequency) [Hz]
    /// ## z : Zeta Damping Ratio
    /// ## r : Initial response of the system
    /// ## gn: Gain
    ///
    void init( x_real f,
              x_real z,
              x_real r,
              x_real gn = 1,
              Accuracy accuracy = Accuracy::LowestAccuracy);

    /// ## overShoot : 1 is 100%
    /// ## time      : in ms
    /// ## These functions change the units internally
    /// ## for ::init
    void initPeakTime( x_real overShoot,
                      x_real peakTime,
                      Accuracy accuracy = Accuracy::LowestAccuracy);
    void initSettlingTime( x_real overShoot,
                          x_real settlingTime,
                          Accuracy accuracy = Accuracy::LowestAccuracy);

    x_real updateValue( x_real msDelta );
protected:
    // void resetValues() override final;

private:
    x_real computeZeta( x_real overShoot );
    void   setAccuracy(Accuracy accuracy);



private:
    constexpr const static auto pi = static_cast<x_real>( 3.14159265358979323846 );

    x_real m_previousProperty;
    x_real m_previousInput;
    x_real m_propertyDrv;
    x_real m_k1, m_k2, m_k3, m_gain;
    x_real m_tolerance;
};

}
#endif // DAMPEDEASING_H
