#include "petridynamicplace.h"

namespace ptn {

PetriDynamicPlace::PetriDynamicPlace():
    m_accumulated{ 0 },
    m_interval{ 3 * 1000 },
    m_intervalsPassed{ 0 },
    m_tokensCount{ 1 }
{
}

void PetriDynamicPlace::setTokensCount(int tkns)
{
    m_tokensCount = tkns;
}

int PetriDynamicPlace::tokensCount() const
{
    return m_tokensCount;
}

void PetriDynamicPlace::setInterval(float timeMs)
{
    m_interval = timeMs;
}

float PetriDynamicPlace::interval() const
{
    return m_interval;
}

void PetriDynamicPlace::update(float delta)
{
    m_accumulated += delta;

    int intervalsPassed = static_cast<int>(m_accumulated / m_interval);
    if (intervalsPassed > 0)
        m_accumulated -= intervalsPassed * m_interval;

    m_intervalsPassed = static_cast<float>( intervalsPassed );



}

}
