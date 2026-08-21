#ifndef DEBUG_H
#define DEBUG_H

#include <misc/debugassert.h>




/// ## If a type does not define "Type::meta_type_name" and "Type::meta_item_name"
/// ## DebugPrint will default to these instead
/// ##
inline static auto meta_type_name(){return "";}
inline static auto meta_item_name(){return "";}
#define QX_UTL_TYPE_NAME()   meta_type_name()
#define QX_UTL_ITEM_NAME()   meta_item_name()


namespace Qx::prv {


/// ## --------------------------------------------------------------------------------

template< Qx::prv::FixedString prefix, int color>
using PrintDebug  = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 1,
                                     Qx::prv::DebugPrint<prefix,color>,
                                     Qx::prv::DebugNone<prefix,color>
                                     >;


using AssertDebug = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 2,
                                       Qx::prv::DebugAssert,
                                       Qx::prv::AssertNone>;

using LoopAssertDebug = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 3,
                                           Qx::prv::DebugAssert,
                                           Qx::prv::AssertNone>;


template< Qx::prv::FixedString prefix, int color>
using ErrorDebug  = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 4,
                                      Qx::prv::DebugPrint<prefix,color>,
                                      Qx::prv::DebugNone<prefix,color>
                                      >;
template< Qx::prv::FixedString prefix, int color>
using WarningDebug  = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 5,
                                      Qx::prv::DebugPrint<prefix,color>,
                                      Qx::prv::DebugNone<prefix,color>
                                      >;
template< Qx::prv::FixedString prefix, int color>
using InfoDebug  = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 6,
                                        Qx::prv::DebugPrint<prefix,color>,
                                        Qx::prv::DebugNone<prefix,color>
                                        >;
template< Qx::prv::FixedString prefix, int color>
using TipsDebug  = std::conditional_t<QX_DEF_DEBUG_LEVEL >= 7,
                                     Qx::prv::DebugPrint<prefix,color>,
                                     Qx::prv::DebugNone<prefix,color>
                                     >;


/// ## --------------------------------------------------------------------------------

#define dbg_print()   Qx::prv::PrintDebug   < "Debug   ", 32>( QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )
#define dbg_error()   Qx::prv::ErrorDebug   < "Error   ", 31>( QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )
#define dbg_warning() Qx::prv::WarningDebug < "Warning ", 36>( QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )
#define dbg_info()    Qx::prv::InfoDebug    < "Info    ", 34>( QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )
#define dbg_tips()    Qx::prv::TipsDebug    < "Tips    ", 33>( QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )


/// ## For static functions
/// ## meta_type_name and meta_item_name, are member methods
/// ## will cause an error in static functions
/// ## So we use "" instead
///
#define dbg_print_st()    Qx::prv::PrintDebug   < "Debug   ", 32>( "", "" )
#define dbg_error_st()    Qx::prv::ErrorDebug   < "Error   ", 31>( "", "" )
#define dbg_warning_st()  Qx::prv::WarningDebug < "Warning ", 36>( "", "" )
#define dbg_info_st()     Qx::prv::InfoDebug    < "Info    ", 34>( "", "" )
#define dbg_tips_st()     Qx::prv::TipsDebug    < "Tips    ", 33>( "", "" )




/// ## --------------------------------------------------------------------------------


#define dbg_assert(cond)     Qx::prv::AssertDebug( cond, QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )
#define dbg_assert_st(cond)  Qx::prv::AssertDebug( cond, "", "" )
/// ## --------------------------------------------------------------------------------


/// ## Used inside render loops
#define dbg_loop_assert(cond)     Qx::prv::LoopAssertDebug( cond, QX_UTL_TYPE_NAME(), QX_UTL_ITEM_NAME() )
#define dbg_loop_assert_st(cond)  Qx::prv::LoopAssertDebug( cond, "", "" )


/// ## --------------------------------------------------------------------------------

#define dbg_unused(val)    (void)(val)

#define dbg_static_assert_same_types( Type0, Type1 ) \
static_assert(sizeof(Type0) == sizeof(Type1), "Type sizes of " #Type0 " and " #Type1 " must match for casting "); \
    static_assert(alignof(Type0) == alignof(Type1), "Type Alignment of " #Type0 " and " #Type1 " must match for casting ");


/// ## --------------------------------------------------------------------------------

}

#endif // DEBUG_H
