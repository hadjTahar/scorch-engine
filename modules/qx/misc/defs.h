#ifndef X_DEFS
#define X_DEFS

#include <vector>
#include <string>
#include <span>

namespace Qx
{

using x_real       = float;
using x_count      = std::size_t;
using x_time       = uint64_t;
using x_channel    = uint8_t;
using x_keycode    = uint32_t;
using x_modifiers  = uint16_t;
using x_rgba       = std::array<x_real,4>;
using x_string     = std::string;
using x_byte       = uint8_t;
using x_data       = std::vector<x_byte>;   /// ## Binary data
using x_dataSpan   = std::span<const x_byte>;

using x_layers     = uint32_t;
// using x_error        = ErrorResult;
// using x_entityType = uint32_t;


}

#endif // X_DEFS
