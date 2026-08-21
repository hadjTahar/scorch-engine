#include "petriengine.h"



#include <sparsematrix.h>
#include <iostream>
#include <assert.h>

namespace ptn {

PetriEngine::PetriEngine():
    m_rows{1},
    m_cols{1}
{

}

PetriEngine::~PetriEngine()
{

}

std::vector<int> PetriEngine::changeMarking() const
{
    const auto sz = m_places.size();
    std::vector<int> ret = {};
    ret.resize( sz );
    for (auto idx = 0; idx < sz; ++idx){
        const auto plc = m_places[ idx ].get();
        ret[ idx ] = plc->tokens() - plc->prevTokens();
    }
    return ret;
}


void PetriEngine::setSize(int places, int transitions)
{
    m_rows = places;
    m_cols = transitions;
}

PetriPlace *PetriEngine::addPlace(int tokens)
{
    return addPlace<PetriPlace>( tokens );
}

PetriTimerPlace *PetriEngine::addTimerPlace(int tokens)
{
    return addPlace<PetriTimerPlace>( tokens );
}

PetriDelayedPlace *PetriEngine::addDelayedPlace(int tokens)
{
    return addPlace<PetriDelayedPlace>( tokens );
}

StochasticPlace *PetriEngine::addStochasticPlace(int tokens)
{
    return addPlace<StochasticPlace>( tokens );
}

PetriTransition *PetriEngine::addTransition()
{
    auto trnPtr = std::make_unique<PetriTransition>();
    auto ret = trnPtr.get();
    m_transitions.push_back( std::move( trnPtr ) );
    return ret;
}

void PetriEngine::step(float delta )
{
    assert(  m_places.size() == m_rows &&
           "Places added and petri net size mismatch");
    assert(  m_transitions.size() == m_cols &&
           "Transitions added and petri net size mismatch");

    for ( auto&& plc : m_places)
        plc->update( delta );

    const auto markings = markingVec();
    const auto firings  = firingVec();
    const auto incidMat = postMat() - preMat();
    auto newMarkings = markings + incidMat * firings;

    for ( auto&& plc : m_places) {
        const auto idx = plc->index();
        const auto tks = newMarkings.get( idx+1, 1 );
        plc->setTokens( tks );
    }

}

void PetriEngine::displayMarking() const
{
    std::cout << " ------------------------- " << std::endl;
    for ( auto&& plc : m_places) {
        const auto idx = plc->index();
        const auto tks = plc->tokens();
        std::cout << idx << " : " << tks << std::endl;
    }
}

PetriPlace *PetriEngine::place(const std::string &name)
{
    if( name.empty() )
        return nullptr;
    PetriPlace *ret = nullptr;
    for ( auto&& plc : m_places)
        if( plc->name() == name ){
            ret = plc.get();
            break;
        }

    return ret;
}

PetriPlace *PetriEngine::place(const int idx)
{
    PetriPlace *ret = nullptr;
    for ( auto&& plc : m_places)
        if( plc->index() == idx ){
            ret = plc.get();
            break;
        }

    return ret;
}

int PetriEngine::tokens(const std::string &name)
{
    const auto plc = place( name );
    if( !plc )
        return -1;
    return plc->tokens();
}

int PetriEngine::tokens(const int idx)
{
    const auto plc = place( idx );
    if( !plc )
        return -1;
    return plc->tokens();
}


PetriEngine::PetriMat PetriEngine::markingVec() const
{
    const auto sz = static_cast<int>( m_places.size() );
    PetriMat ret( sz, 1);

    for ( auto&& plc : m_places) {
        const auto idx = plc->index();
        // std::cout << idx << " : " << plc->tokens() << std::endl;
        ret.set( plc->tokens(), idx+1, 1 );
    }
    return ret;

}

PetriEngine::PetriMat PetriEngine::firingVec() const
{
    const auto sz = static_cast<int>( m_transitions.size() );
    PetriMat ret( sz, 1);

    for ( auto&& tr : m_transitions) {
        const int en = tr->enabled()? 1 : 0;
        const auto jdx = tr->index();
        ret.set( en, jdx+1, 1 );
    }
    return ret;
}

PetriEngine::PetriMat PetriEngine::preMat() const
{

    PetriMat ret( m_rows, m_cols);

    const auto placesCnt = m_places.size();
    for ( auto&& tr : m_transitions) {
        const auto jdx = tr->index();
        for (auto idx = 0; idx < placesCnt; ++idx) {
            const auto w = tr->inletWeight( idx );
            ret.set( w,idx+1, jdx+1);
        }
    }
    return ret;
}

PetriEngine::PetriMat PetriEngine::postMat() const
{
    PetriMat ret( m_rows, m_cols);

    const auto placesCnt = m_places.size();
    for ( auto&& tr : m_transitions) {
        const auto jdx = tr->index();
        for (auto idx = 0; idx < placesCnt; ++idx) {
            const auto w = tr->outletWeight( idx );
            ret.set( w,idx+1, jdx+1);
        }
    }
    return ret;
}

}
