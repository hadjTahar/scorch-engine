#ifndef POLYNOMIALEASING_H
#define POLYNOMIALEASING_H

#include "durationeasing.h"

#include <misc/callbacks.h>

#include <cmath>
#include <numbers>


namespace Qx
{

class PolynomialEasing : public prv::DurationEasing
{
public:
    PolynomialEasing();
    x_real updateValue( x_real msDelta );
    prv::x_polynomialCallback polynomial;


};


struct Easing
{
    // Constants used in the original easing equations
    inline static constexpr x_real PI = static_cast<x_real>( std::numbers::pi );
    inline static constexpr x_real c1 = 1.70158f;
    inline static constexpr x_real c2 = c1 * 1.525f;
    inline static constexpr x_real c3 = c1 + 1.0f;
    inline static constexpr x_real c4 = (2.0f * PI) / 3.0f;
    inline static constexpr x_real c5 = (2.0f * PI) / 4.5f;



    // Dependency for Bounce functions
    inline static const auto EaseOutBounce = [](x_real x) -> x_real {
        const x_real n1 = 7.5625f;
        const x_real d1 = 2.75f;

        if (x < 1 / d1) {
            return n1 * x * x;
        } else if (x < 2.f / d1) {
            return n1 * (x -= 1.5f / d1) * x + 0.75f;
        } else if (x < 2.5f / d1) {
            return n1 * (x -= 2.25f / d1) * x + 0.9375f;
        } else {
            return n1 * (x -= 2.625f / d1) * x + 0.984375f;
        }
    };






    // Linear
    inline static const auto  Linear = [](x_real x) { return x; };

    // Quadratic
    inline static const auto EaseInQuad = [](x_real x) { return x * x; };
    inline static const auto EaseOutQuad = [](x_real x) { return 1.0f - (1.0f - x) * (1.0f - x); };
    inline static const auto EaseInOutQuad = [](x_real x) {
        return x < 0.5f ? 2.0f * x * x : 1.0f - std::powf(-2.0f * x + 2.0f, 2) / 2.0f;
    };

    // Cubic
    inline static const auto EaseInCubic = [](x_real x) { return x * x * x; };
    inline static const auto EaseOutCubic = [](x_real x) { return 1.0f - std::powf(1.0f - x, 3); };
    inline static const auto EaseInOutCubic = [](x_real x) {
        return x < 0.5f ? 4.0f * x * x * x : 1.0f - std::powf(-2.0f * x + 2.0f, 3) / 2.0f;
    };

    // Quartic
    inline static const auto EaseInQuart = [](x_real x) { return x * x * x * x; };
    inline static const auto EaseOutQuart = [](x_real x) { return 1.0f - std::powf(1.0f - x, 4); };
    inline static const auto EaseInOutQuart = [](x_real x) {
        return x < 0.5f ? 8.0f * x * x * x * x : 1.0f - std::powf(-2.0f * x + 2.0f, 4) / 2.0f;
    };

    // Quintic
    inline static const auto EaseInQuint = [](x_real x) { return x * x * x * x * x; };
    inline static const auto EaseOutQuint = [](x_real x) { return 1.0f - std::powf(1.0f - x, 5); };
    inline static const auto EaseInOutQuint = [](x_real x) {
        return x < 0.5f ? 16.0f * x * x * x * x * x : 1.0f - std::powf(-2.0f * x + 2.0f, 5) / 2.0f;
    };

    // Sine
    inline static const auto EaseInSine = [](x_real x) { return 1.0f - std::cosf((x * PI) / 2.0f); };
    inline static const auto EaseOutSine = [](x_real x) { return std::sinf((x * PI) / 2.0f); };
    inline static const auto EaseInOutSine = [](x_real x) { return -(std::cosf(PI * x) - 1.0f) / 2.0f; };

    // Exponential
    inline static const auto EaseInExpo = [](x_real x) {
        return x == 0.0f ? 0.0f : std::powf(2.0f, 10.0f * x - 10.0f);
    };
    inline static const auto EaseOutExpo = [](x_real x) {
        return x == 1.0f ? 1.0f : 1.0f - std::powf(2.0f, -10.0f * x);
    };
    inline static const auto EaseInOutExpo = [](x_real x) {
        if (x == 0.0f) return 0.0f;
        if (x == 1.0f) return 1.0f;
        return x < 0.5f ? std::powf(2.0f, 20.0f * x - 10.0f) / 2.0f : (2.0f - std::powf(2.0f, -20.0f * x + 10.0f)) / 2.0f;
    };

    // Circular
    inline static const auto EaseInCirc = [](x_real x) { return 1.0f - std::sqrtf(1.0f - std::powf(x, 2)); };
    inline static const auto EaseOutCirc = [](x_real x) { return std::sqrtf(1.0f - std::powf(x - 1.0f, 2)); };
    inline static const auto EaseInOutCirc = [](x_real x) {
        return x < 0.5f ? (1.0f - std::sqrtf(1.0f - std::powf(2.0f * x, 2))) / 2.0f
                       : (std::sqrtf(1.0f - std::powf(-2.0f * x + 2.0f, 2)) + 1.0f) / 2.0f;
    };

    // Back
    inline static const auto EaseInBack = [](x_real x) { return c3 * x * x * x - c1 * x * x; };
    inline static const auto EaseOutBack = [](x_real x) {
        return 1.0f + c3 * std::powf(x - 1.0f, 3) + c1 * std::powf(x - 1.0f, 2);
    };
    inline static const auto EaseInOutBack = [](x_real x) {
        return x < 0.5f ? (std::powf(2.0f * x, 2) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f
                       : (std::powf(2.0f * x - 2.0f, 2) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
    };

    // Elastic
    inline static const auto EaseInElastic = [](x_real x) {
        if (x == 0.0f) return 0.0f;
        if (x == 1.0f) return 1.0f;
        return -std::powf(2.0f, 10.0f * x - 10.0f) * std::sinf((x * 10.0f - 10.75f) * c4);
    };
    inline static const auto EaseOutElastic = [](x_real x) {
        if (x == 0.0f) return 0.0f;
        if (x == 1.0f) return 1.0f;
        return std::powf(2.0f, -10.0f * x) * std::sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
    };
    inline static const auto EaseInOutElastic = [](x_real x) {
        if (x == 0.0f) return 0.0f;
        if (x == 1.0f) return 1.0f;
        return x < 0.5f ?
                   -(std::powf(2.0f, 20.0f * x - 10.0f) * std::sinf((20.0f * x - 11.125) * c5)) / 2.0f :
                   ( std::powf(2.0f, -20.0f * x + 10.0f) * std::sinf((20.0f * x - 11.125) * c5)) / 2.0f + 1.0f;
    };

    // Bounce
    inline static const auto EaseInBounce = [](x_real x) { return 1.0f - EaseOutBounce(1.0f - x); };
    inline static const auto EaseInOutBounce = [](x_real x) {
        return x < 0.5f ? (1.0f - EaseOutBounce(1.0f - 2.0f * x)) / 2.0f
                       : (1.0f + EaseOutBounce(2.0f * x - 1.0f)) / 2.0f;
    };
};



}

#endif // POLYNOMIALEASING_H
