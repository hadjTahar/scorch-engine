// #ifndef PHYSICSPROPERTIES_H
// #define PHYSICSPROPERTIES_H

// #include "properties.h"
// #include <type_traits>


// namespace Qx::prv
// {



// template<int N>
// struct KinematicsProperties
// {
//     static_assert(N==2 || N==3, "N cn only be 2 or 4" );
//     // World position
//     std::conditional_t< N==2, x_vector2, x_vector3> position;
//      // Orientation (angle in radians)
//     std::conditional_t< N==2, x_real, x_quat> rotation;
//     // Linear velocity
//     std::conditional_t< N==2, x_vector2, x_vector3> velocity;
//     // Rotational velocity (radians/sec)
//     std::conditional_t< N==2, x_real, x_vector3> angularVelocity;
// };

// template<int N>
// struct InertiaProperties
// {
//     static_assert(N==2 || N==3, "N cn only be 2 or 4" );
//     // Mass (kg)
//     std::conditional_t< N==2, x_real, x_real> mass;
//     // Precomputed 1/mass
//     std::conditional_t< N==2, x_real, x_real> inverseMass;
//     // Moment of inertia (scalar)
//     std::conditional_t< N==2, x_real, x_matrix3x3> inertiaTensor;
//     // Precomputed inverse
//     std::conditional_t< N==2, x_real, x_matrix3x3> inverseInertia;
// };


// template<int N>
// struct ForceProperties
// {
//     static_assert(N==2 || N==3, "N cn only be 2 or 4" );
//     // // Accumulated linear forces this frame
//     std::conditional_t< N==2, x_vector2, x_vector3> forceAccum;
//     // Accumulated torque this frame
//     std::conditional_t< N==2, x_real, x_vector3> torqueAccum;
// };


// enum class Shape2DType { Box, Circle, Polygon };
// enum class Shape3DType { Box, Circle, Polygon };

// template<int N>
// struct ColliderProperties
// {
//     static_assert(N==2 || N==3, "N cn only be 2 or 4" );

//     Shape2DType type;
//     // For Box
//     std::conditional_t< N==2, x_vector2, x_vector3> halfExtents;
//     // Accumulated torque this frame
//     std::conditional_t< N==2, x_real, x_real> radius;
//     // Polygon points could be added later if needed
// };


// struct MaterialProperties
// {
//     x_real restitution;     // Bounciness [0..1]
//     x_real friction;        // Friction [0..1]
// };


// struct PhysicsProperties
// {
//     bool isStatic;          // Immovable object
//     bool awake;             // Whether the object is active in physics simulation
// };



// }


// #endif // PHYSICSPROPERTIES_H
