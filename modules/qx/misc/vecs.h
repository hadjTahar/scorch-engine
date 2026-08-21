#ifndef X_MATH_H
#define X_MATH_H

#include "defs.h"
#include "flags.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/quaternion.hpp>
// Optionally, for quaternion-to-matrix conversions:
// #include <glm/gtx/quaternion.hpp>
#include <SDL3/SDL_rect.h>

#include <vector>
#include <fstream>


namespace Qx
{
    // Use 4x4 matrix ( for 2D use only the 3x3 part)


namespace x_vector   = glm;
using x_vector2      = glm::vec2;
using x_vector3      = glm::vec3;
using x_vector4      = glm::vec4;
using x_quat         = glm::quat;
using x_matrix3x3    = glm::mat3x3;
using x_matrix4x4    = glm::mat4x4;
// using x_vindex       = uint16_t; /// ## Vertex Index

struct x_size
{
    bool operator==(const x_size&) const = default;
    x_real 	width{0};
    x_real 	height{0};
    x_real 	depth{0};
};

struct x_radius
{
    bool operator==(const x_radius&) const = default;
    x_real 	leftRad{0};
    x_real 	topRad{0};
    x_real 	rightRad{0};
    x_real 	bottomRad{0};
};

struct x_rect
{
    // bool operator==(const x_rect&) const = default;
    x_real 	x{0};
    x_real 	y{0};
    x_real 	width{0};
    x_real 	height{0};
};


struct x_pivot
{
    PivotType type = PivotType::None;

    PivotAxis x = PivotAxis::Min;
    PivotAxis y = PivotAxis::Min;
    PivotAxis z = PivotAxis::Min;

    x_vector3 custom{};
};

struct x_rrect
{
    x_rect   rect;
    x_radius radius;
};


using v_matData    = std::vector<char>;   /// ## Binary data
/// ## Vertex count and index, for filament
using v_count      = uint32_t;
using v_index      = uint16_t;
using v_position   = x_vector3;
using v_uv         = x_vector2;

using v_indices   = std::vector<v_index>;
using v_positions = std::vector<v_position>;
using v_uvs       = std::vector<v_uv>;

// struct v_vertex {
//     x_vector3 position;
//     x_vector2 uv;
// };

struct x_aabb {

    x_vector3 min{};
    x_vector3 max{};
};


static v_matData loadFilamatFile(const std::string& filePath)
{
    // dbgw
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open material file: " + filePath);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    v_matData buffer(size);
    if (!file.read(buffer.data(), size)) {
        throw std::runtime_error("Failed to read material data");
    }
    return buffer;
}




}


#endif // X_MATH_H
