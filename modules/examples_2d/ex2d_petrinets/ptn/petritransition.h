#ifndef PETRITRANSITION_H
#define PETRITRANSITION_H

#include <vector>

namespace ptn {

class PetriPlace;

struct PetriArc
{
    PetriPlace *place;
    int         weight;
};

class PetriTransition
{
public:
    PetriTransition();
    void linkIn( PetriPlace* plc, int weight );
    void linkOut( PetriPlace* plc, int weight );
    int  inletWeight(int placeIdx) const;
    int  outletWeight( int placeIdx ) const;
    bool enabled() const;

    uint32_t index() const;

protected:
    uint32_t m_index;
    static uint32_t m_indexCounter;


    std::vector<PetriArc>      m_inlets;
    std::vector<PetriArc>      m_outlets;
};

}
#endif // PETRITRANSITION_H
