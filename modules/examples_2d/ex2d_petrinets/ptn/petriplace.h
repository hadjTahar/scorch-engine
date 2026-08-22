#ifndef PETRIPLACE_H
#define PETRIPLACE_H

#include <vector>
#include <memory>
#include <string>

namespace ptn {

enum class PlaceType { Generic, Delayed, Timer, Stochastic };

class PetriPlace
{


public:
    PetriPlace();
    virtual ~PetriPlace();
    int tokens() const;
    virtual void addTokens(int newtokens);

    uint32_t index() const;

    std::string name() const;
    void setName(const std::string &newName);


protected:
    friend class PetriEngine;
    int prevTokens() const;
    void setTokens(int newtokens);
    virtual void update( float){}

protected:

    uint32_t m_index;
    static uint32_t m_indexCounter;
    int m_tokens;
    int m_prevTokens;
    PlaceType m_type;
    std::string m_name;
};

}
#endif // PETRIPLACE_H
