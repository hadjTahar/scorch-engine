#ifndef PETRIDELAYEDPLACE_H
#define PETRIDELAYEDPLACE_H

#include "petridynamicplace.h"


namespace ptn {

class PetriDelayedPlace : public PetriDynamicPlace
{

public:
    PetriDelayedPlace();
    void addTokens(int newtokens) override;

protected:
    void update( float delta ) override;

protected:
    /// ## Count, delta time
    /// ## keep adding delta to .second
    /// ## if .second >= interval add
    ///
    /// ## Override add tokens/settokens???
    std::vector<std::pair<int, float> > m_delayedTokens;
};

}

#endif // PETRIDELAYEDPLACE_H
