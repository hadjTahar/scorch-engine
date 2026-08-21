#ifndef DEBUGASSERT_H
#define DEBUGASSERT_H

#include <sstream>
#include <source_location>
#include <misc/debugprint.h>



namespace Qx::prv
{

class AssertNone : public DebugNone < "Assert  ", 31>
{
public:
    AssertNone(
        bool,
        const std::string &tpName,
        const std::string &itmName,
        const std::source_location location =
        std::source_location::current()
        ):
        DebugNone{ tpName, itmName, location }
    {
    }
};

class DebugAssert : public DebugPrint < "Assert  ", 31>
{

    /// ## Disable copying
public:
    DebugAssert(
        bool cond,
        const std::string &tpName,
        const std::string &itmName,
        const std::source_location location =
        std::source_location::current()
        ):
        DebugPrint{ tpName, itmName, location },
        m_condition{ cond }
    {
    }
    ~DebugAssert()
    {
        if( m_condition ){
            m_display = false;
            m_abort   = false;
        }
        else{
            m_display = true;
            m_abort   = true;
        }

    }

private:
    std::ostringstream  m_oss;
    bool                m_condition;
};



}

#endif // DEBUGASSERT_H
