#ifndef PETRITIMERPLACE_H
#define PETRITIMERPLACE_H

#include "petridynamicplace.h"


namespace ptn {

class PetriTimerPlace : public PetriDynamicPlace
{


public:
    PetriTimerPlace();
    void addTokens(int ) override;

protected:
    void update( float delta ) override;
};

}
#endif // PETRITIMERPLACE_H
