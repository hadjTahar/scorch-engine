#ifndef CANVASEFFECTS_H
#define CANVASEFFECTS_H

namespace Qx::prv
{

// enum class EffectsType
// {
//     ClearAll = 0,
//     GaussianBlur,
//     DropShadow,
//     Fill,
//     Tint,
//     Tritone

// };

// struct CanvasEffects
// {
//     EffectsType type{EffectsType::ClearAll};
//     x_channel r{0};
//     x_channel g{0};
//     x_channel b{0};
//     x_channel a{255};
//     x_real angle{0.0};
//     x_real distance{0.0};
//     x_real sigma{0.0};
//     x_real quality{100.0};


//     inline static CanvasEffects elevation(int value)
//     {
//         // Clamp elevation range (Material Design 3 typically 1–12dp)
//         if (value < 1) value = 1;
//         if (value > 12) value = 12;

//         CanvasEffects shadow;
//         shadow.type = prv::EffectsType::DropShadow;

//         // MD3 shadows are pure black with varying opacity
//         shadow.r = 0;
//         shadow.g = 0;
//         shadow.b = 0;

//         // Opacity in MD3 is subtle — softer at low levels, denser at high
//         // Values tuned to match MD3 guidelines (ambient + key combined look)
//         static constexpr int alphaLUT[13] = {
//             0,  /* unused */
//             38,  /* dp1 */
//             50,  /* dp2 */
//             62,  /* dp3 */
//             74,  /* dp4 */
//             88,  /* dp5 */
//             100, /* dp6 */
//             112, /* dp7 */
//             124, /* dp8 */
//             136, /* dp9 */
//             148, /* dp10 */
//             150, /* dp11 */
//             100  /* dp12 */
//         };
//         shadow.a = static_cast<int>( .65f * alphaLUT[value] );

//         // Shadows in MD3 fall directly downwards
//         shadow.angle = 180.0;

//         // Distance grows roughly linearly with dp
//         // (slightly exaggerated for visibility in single-shadow mode)
//         shadow.distance = static_cast<x_real>(0.9 * value);

//         // Blur grows faster than distance for that soft MD3 glow
//         static constexpr float sigmaLUT[13] = {
//             0.0f,  /* unused */
//             1.5f,  /* dp1 */
//             3.0f,  /* dp2 */
//             4.5f,  /* dp3 */
//             6.0f,  /* dp4 */
//             7.5f,  /* dp5 */
//             9.0f,  /* dp6 */
//             10.5f, /* dp7 */
//             12.0f, /* dp8 */
//             13.5f, /* dp9 */
//             15.0f, /* dp10 */
//             16.5f, /* dp11 */
//             20.0f  /* dp12 */
//         };
//         shadow.sigma = 0.962f * sigmaLUT[value];

//         // Keep rendering quality high
//         shadow.quality = 100.0;

//         return shadow;
//     }
// };

}


#endif // CANVASEFFECTS_H
