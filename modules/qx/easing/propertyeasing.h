#ifndef PROPERTYEASING_H
#define PROPERTYEASING_H

#include <misc/defs.h>

namespace Qx::prv
{

class PropertyEasing
{
public:
    PropertyEasing();
    x_real property() const;


    bool done() const;
    x_real value;
    x_real m_property;
    bool   m_done;

};

}

#endif // PROPERTYEASING_H
