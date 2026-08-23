#include "petriplace.h"

namespace ptn {

uint32_t PetriPlace::m_indexCounter = 0;

PetriPlace::PetriPlace():
    m_index{ m_indexCounter },
    m_tokens{ 0 },
    m_prevTokens{ 0 },
    m_type{ PlaceType::Generic },
    m_name{ "" }
{
    ++m_indexCounter;
}

PetriPlace::~PetriPlace()
{

}

int PetriPlace::tokens() const
{
    return m_tokens;
}

void PetriPlace::addTokens(int newtokens)
{
    setTokens( m_tokens + newtokens );
}

uint32_t PetriPlace::index() const
{
    return m_index;
}

std::string PetriPlace::name() const
{
    return m_name;
}

void PetriPlace::setName(const std::string &newName)
{
    m_name = newName;
}

void PetriPlace::setTokens(int newtokens)
{
    m_prevTokens = m_tokens;
    m_tokens = newtokens;
}

int PetriPlace::prevTokens() const
{
    return m_prevTokens;
}

}
