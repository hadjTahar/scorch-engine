#include "propertyeasing.h"

namespace Qx::prv
{

PropertyEasing::PropertyEasing():
    value{ 0 },
    m_done{ false },
    m_property{ 0 }
{

}

x_real PropertyEasing::property() const
{
    return m_property;
}

bool PropertyEasing::done() const
{
    return m_done;
}

}
