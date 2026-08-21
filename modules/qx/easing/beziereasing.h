#ifndef BEZIEREASING_H
#define BEZIEREASING_H

#include "durationeasing.h"
#include <misc/vecs.h>
#include <array>


namespace Qx
{

class BezierEasing : public prv::DurationEasing
{
    using controls = std::array<x_vector2, 4>;

public:
    BezierEasing();
    x_real valueAt( const x_real t ) const ;
    x_real updateValue( x_real msDelta );

protected:
    std::vector<x_vector2> reduce(const std::vector<x_vector2> &pts,
                                  const x_real t ) const;

public:
    x_vector2   &control0;
    x_vector2   &control1;
    controls    m_controls;
};

}

#endif // BEZIEREASING_H
