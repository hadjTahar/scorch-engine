#include "petridelayedplace.h"

namespace ptn {

PetriDelayedPlace::PetriDelayedPlace()
{
    m_type = PlaceType::Delayed;
}

void PetriDelayedPlace::addTokens(int newtokens)
{
    m_delayedTokens.push_back( { newtokens, .0f } );
}

void PetriDelayedPlace::update(float delta)
{
    PetriDynamicPlace::update( delta );

    std::vector<std::pair<int, float> > newTokens;
    newTokens.reserve( m_delayedTokens.size() );

    for ( auto &pair : m_delayedTokens) {
        pair.second += delta;
        if( pair.second >= m_interval )
            PetriDynamicPlace::addTokens( pair.first );
        else newTokens.push_back( pair );
    }
    m_delayedTokens = newTokens;
}




}
