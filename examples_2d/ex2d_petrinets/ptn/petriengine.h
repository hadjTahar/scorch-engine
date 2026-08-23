#ifndef PETRIENGINE_H
#define PETRIENGINE_H

#include <sparsematrix.h>
#include "petritimerplace.h"
#include "petritransition.h"
#include "petridelayedplace.h"
#include "stochasticplace.h"

#include <vector>
#include <memory>


namespace ptn {

class PetriTimerPlace;

class PetriEngine
{
    using PetriMat = ptn::SparseMatrix<int>;

public:
    PetriEngine();
    ~PetriEngine();
    std::vector<int> changeMarking() const;


    void setSize( int places, int transitions );


    template< class PlaceType>
    PlaceType *addPlace( int tokens = 0 )
    {
        auto plcPtr = std::make_unique<PlaceType>();
        auto ret = plcPtr.get();
        m_places.push_back( std::move( plcPtr ) );
        ret->setTokens( tokens );
        return ret;
    }

    PetriPlace *addPlace( int tokens = 0 );
    PetriTimerPlace *addTimerPlace( int tokens = 0 );
    PetriDelayedPlace *addDelayedPlace( int tokens = 0 );
    StochasticPlace *addStochasticPlace( int tokens = 0 );
    PetriTransition *addTransition();


    void step(float delta);
    void displayMarking() const;

    PetriPlace* place( const std::string &name );
    PetriPlace* place( const int idx );

    int tokens( const std::string &name );
    int tokens( const int idx );


protected:
    PetriMat preMat() const;
    PetriMat postMat() const;
    PetriMat markingVec() const;
    PetriMat firingVec() const;


protected:


    std::vector<std::unique_ptr<PetriPlace> >      m_places;
    std::vector<std::unique_ptr<PetriTransition> > m_transitions;
    /// ## palce index, new count
    ///
    int      m_rows;
    int      m_cols;

};

}

#endif // PETRIENGINE_H
