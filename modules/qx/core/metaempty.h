#ifndef METAEMPTY_H
#define METAEMPTY_H

#include "metaempty.h"
#include <misc/flags.h>
#include <misc/defs.h>
#include <misc/debugprint.h>

#include <map>
#include <memory>
#include <set>



namespace Qx::prv
{

struct MetaEmpty
{
    /// ## --------------------------------------------------------
    /// ## Bool support
    MetaEmpty(const bool ){}
    MetaEmpty& operator=(const bool )
    {
        return *this;
    }
    operator bool() const
    {
        return true;
    }


    /// ## --------------------------------------------------------
    /// ## MetaItemType support
    MetaEmpty(const MetaItemType ){}
    MetaEmpty& operator=(const MetaItemType )
    {
        return *this;
    }
    operator Qx::prv::MetaItemType() const
    {
        return MetaItemType::NA;
    }

    /// ## --------------------------------------------------------
    /// ## String support
    // 1. Construct from std::string (Implicit)
    // Note: No 'explicit' keyword here allows implicit conversion
    // MetaEmpty(const char* ){}
    // MetaEmpty(const std::string& ){}
    // // 2. Copy Constructor
    // MetaEmpty(const MetaEmpty& ){}
    // // 3. Convert to std::string (Implicit)
    // operator std::string() const{return "0";}
    // operator const char*() const { return "0"; }

    // // 4. Assignment Operator (Copy from a std::string)
    // MetaEmpty& operator=(const std::string& ){return *this;}
    // MetaEmpty& operator=(const char* ){return *this;}

    // // 5. Stream Insertion Operator
    // friend std::ostream& operator<<(std::ostream& os, const MetaEmpty& ){return os;}
};


// inline bool has_any(MetaEmpty value, MetaEmpty flags) noexcept
// {
//     return true;
// }

// inline bool operator&(MetaEmpty, MetaEmpty) noexcept
// {
//     return true;
// }


}



#endif // METAEMPTY_H
