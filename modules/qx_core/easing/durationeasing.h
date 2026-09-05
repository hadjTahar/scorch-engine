#ifndef DURATIONEASING_H
#define DURATIONEASING_H

#include "propertyeasing.h"



namespace Qx::prv
{

class DurationEasing : public PropertyEasing
{
public:
    DurationEasing();


protected:
    x_real stepTime( x_real msDelta );

public:
    x_real duration;

protected:
    x_real m_t;
};

}

#endif // DURATIONEASING_H
