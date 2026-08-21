#include "petritimerplace.h"
#include <iostream>

namespace ptn {

PetriTimerPlace::PetriTimerPlace()
{
    m_type = PlaceType::Timer;
}

void PetriTimerPlace::addTokens(int )
{

}

void PetriTimerPlace::update(float delta)
{
    PetriDynamicPlace::update( delta );
    const auto tkns = static_cast<int>( m_intervalsPassed * m_tokensCount );
    setTokens( tkns );
}




}
