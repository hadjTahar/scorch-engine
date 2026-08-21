#ifndef X_DEBUGPRINT_H
#define X_DEBUGPRINT_H


#include <misc/vecs.h>
#include <misc/defs.h>


#include <sstream>
#include <source_location>
#include <regex>
#include <iostream>





namespace Qx::prv {


template<x_count N>
struct FixedString {
    char data[N]{};

    constexpr FixedString(const char (&str)[N]) {
        std::copy_n(str, N, data);
    }

    std::string text() const
    {
        std::string ret;
        ret.resize( N, ' ' );
        std::copy_n(data, N, ret.data());

        // std::cout << "++++++++++++ : " << ret;
        return ret;
    }

    // 1. Compare with another FixedString of any size
    template<x_count M>
    constexpr bool operator==(const FixedString<M>& other) const {
        return std::string_view(data, N) == std::string_view(other.data, M);
    }

    // 2. Compare with std::string_view (handles std::string and const char* automatically)
    constexpr bool operator==(std::string_view secondary) const {
        // Exclude the null terminator from our comparison if present
        std::string_view primary(data, N - 1);
        return primary == secondary;
    }
};

// 3. Global overload to allow left-hand side comparisons (e.g., "text" == fixed_str)
template<x_count N>
constexpr bool operator==(std::string_view lhs, const FixedString<N>& rhs) {
    return rhs == lhs; // Reuses the member operator
}

/// ## ------------------------------------------------------------------


template< FixedString prefix, int color>
class DebugNone {

public:

    inline DebugNone(
        const std::string &,
        const std::string &,
        const std::source_location=
        std::source_location::current()
        )
        {

        }

    template <typename T>
    DebugNone& operator<<(const T& ) { return *this;}
    DebugNone& operator<<(std::ostream& (*os)(std::ostream&))
    {
        return *this;
    }
};


/// ## ------------------------------------------------------------------


template< FixedString prefix, int color>
class DebugPrint {


    /// ## Disable copying
public:
    inline DebugPrint(
        const std::string &tpName,
        const std::string &itmName,
        const std::source_location location =
        std::source_location::current()
        )
    {
        if constexpr( QX_DEF_DEBUG_DETAILS == 0 )
            return;


        std::string txt = "";
        const auto callerName = extractMethod( location.function_name() );
        if constexpr( QX_DEF_DEBUG_DETAILS > 1 )
            txt+= prefix.text();
        if( !callerName.empty() && QX_DEF_DEBUG_DETAILS > 2 )
            txt+= "at " + callerName + ",";
        if( !tpName.empty()   && QX_DEF_DEBUG_DETAILS > 3  )
            txt+= tpName + ",";
        if( !itmName.empty()   && QX_DEF_DEBUG_DETAILS > 4  )
            txt+= itmName + ",";

        if (txt.ends_with(","))
            txt.pop_back();

        if( !txt.empty() )
            txt = "("+txt+") : ";
        m_oss << txt  << "\033[" << color << "m";
    }


    inline ~DebugPrint()
    {
        if constexpr( QX_DEF_DEBUG_DETAILS == 0 )
            return;


        /// ## For asserts
        if( !m_display )
            return;

        m_oss << "\033[0m";
        std::cout << m_oss.str() << std::endl;

        if( m_abort )
            abort();

    }


    std::string extractMethod(const std::string& input)
    {
        if constexpr( QX_DEF_DEBUG_DETAILS == 0 )
            return "";
        std::regex pattern(R"(\b([\w\d_]+::[\w\d_]+)\s*\()");
        std::smatch match;

        if (std::regex_search(input, match, pattern)) {
            return match[1]; // Extract "type::method"
        }
        return ""; // Return empty if no match found
    }


    template <typename T>
    DebugPrint& operator<<(const T& value) { m_oss << value;return *this;}
    DebugPrint& operator<<(std::ostream& (*os)(std::ostream&))
    {
        if constexpr( QX_DEF_DEBUG_DETAILS == 0 )
            m_oss << os;
        return *this;
    }


protected:
    std::ostringstream m_oss;
    bool               m_display{true};
    bool               m_abort{false};
};




}


#endif // X_DEBUGPRINT_H
