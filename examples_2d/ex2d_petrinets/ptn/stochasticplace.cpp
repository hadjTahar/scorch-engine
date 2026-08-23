#include "stochasticplace.h"

namespace ptn {

StochasticPlace::StochasticPlace():
    m_generator{ .001f }
{
    m_type = PlaceType::Stochastic;
}

void StochasticPlace::setRatePerSecond(float rate)
{
    m_generator = { rate };
}

void StochasticPlace::addTokens(int)
{
}

void StochasticPlace::update(float delta)
{
    const auto res = m_generator.generate( delta );
    if( res != 1 )
        return;
    PetriDynamicPlace::addTokens( 1 );
}


}
