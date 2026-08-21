#ifndef STOCHASTICPLACE_H
#define STOCHASTICPLACE_H

#include "petridynamicplace.h"
#include "petristochasticgenerator.h"


namespace ptn {



class StochasticPlace : public PetriDynamicPlace
{
public:

    StochasticPlace();
    void setRatePerSecond( float rate );
    void addTokens(int ) override;

protected:
    void update( float delta ) override;

private:
    PetriStochasticGenerator m_generator;

};

}

#endif // STOCHASTICPLACE_H
