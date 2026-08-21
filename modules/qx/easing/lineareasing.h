#ifndef LINEAREASING_H
#define LINEAREASING_H

#include "durationeasing.h"


namespace Qx
{

class LinearEasing : public prv::DurationEasing
{
public:
    LinearEasing();
    x_real updateValue( x_real msDelta );
};

}

#endif // LINEAREASING_H
