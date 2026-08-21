#include "petritransition.h"

#include "petriplace.h"


namespace ptn {

uint32_t PetriTransition::m_indexCounter = 0;

PetriTransition::PetriTransition():
    m_index{ m_indexCounter }
{
    ++m_indexCounter;
}

void PetriTransition::linkIn(PetriPlace *plc, int weight)
{
    m_inlets.push_back( {plc, weight} );
}

void PetriTransition::linkOut(PetriPlace *plc, int weight)
{
    m_outlets.push_back( {plc, weight} );
}
int PetriTransition::inletWeight(int placeIdx) const
{
    for ( auto arc : m_inlets) {
        if( arc.place->index() == placeIdx )
            return arc.weight;
    }
    return 0;
}

int PetriTransition::outletWeight(int placeIdx) const
{
    for ( auto arc : m_outlets) {
        if( arc.place->index() == placeIdx )
            return arc.weight;
    }
    return 0;
}

bool PetriTransition::enabled() const
{
    auto ret = true;
    for ( auto arc : m_inlets) {
        ret = ret && arc.place->tokens() >= arc.weight;
    }
    return ret;
}

uint32_t PetriTransition::index() const
{
    return m_index;
}


}
