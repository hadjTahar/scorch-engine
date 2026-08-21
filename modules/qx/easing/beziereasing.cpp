#include "beziereasing.h"


namespace Qx
{



BezierEasing::BezierEasing():
    m_controls{ x_vector2{.0f,.0f},
                 x_vector2{.25f,.25f},
                 x_vector2{.75f,.75f},
                 x_vector2{1.f,1.f}
      },
    control0{ m_controls[1] },
    control1{ m_controls[2] }
{
}

x_real BezierEasing::valueAt(const x_real t) const
{
    if( t >= 1 )
        return 1;
    std::vector<x_vector2> tmp(m_controls.cbegin(), m_controls.cend());
    while ( tmp.size() > 1 )
        tmp = reduce( tmp, t );
    return tmp[ 0 ].y;
}

x_real BezierEasing::updateValue(x_real msDelta)
{

    if( m_done )
        return m_property;
    const auto t = stepTime( msDelta );
    if( m_done )
        m_property = value;
    else{
        const auto val = valueAt( t );
        m_property = val * value;
    }
    return m_property;


}

std::vector<x_vector2> BezierEasing::reduce(const std::vector<x_vector2> &pts,
                                          const x_real t) const
{
    /// ## https://mmrndev.medium.com/understanding-b%C3%A9zier-curves-f6eaa0fa6c7d

    const auto cnt = pts.size() - 1;
    std::vector<x_vector2> newpoints;
    newpoints.reserve( cnt );

    for (auto idx = 0; idx < cnt; ++idx) {
        const x_real x = (1-t) * pts[ idx ].x + t * pts[ idx+1 ].x;
        const x_real y = (1-t) * pts[ idx ].y + t * pts[ idx+1 ].y;
        newpoints.push_back( { x, y} );
    }

    return newpoints;
}


}
