#ifndef PETRIDYNAMICPLACE_H
#define PETRIDYNAMICPLACE_H

#include "petriplace.h"

namespace ptn {

class PetriDynamicPlace : public PetriPlace
{
public:
    PetriDynamicPlace();


    void setTokensCount( int tkns );
    int tokensCount() const;

    void setInterval( float timeMs );
    float interval() const;

protected:
    void update( float delta ) override;

protected:
    float m_accumulated;
    float m_interval;
    float m_intervalsPassed;
    int   m_tokensCount;
};

}

#endif // PETRIDYNAMICPLACE_H
