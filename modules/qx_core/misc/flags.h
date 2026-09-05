#ifndef FLAGS_H
#define FLAGS_H


#pragma once

#include <type_traits>
#include <cstdint>



namespace Qx
{


enum class FocusPolicy{
    None,
    User,
    Tab,    /// ## + User
    Click,  /// ## + User
    Strong, /// ## User + Tab + Click
    Wheel,  /// ## User + Tab + Click + Wheel

    /// ## Always get the events, does not need focus
    /// ## Eg:game entities, or camera controls
    ///
    Always
};

enum class MousePolicy{
    CheckCapture,
    AlwaysCapture

};


enum class MouseEventType{
    MouseNone,
    MousePress,
    MouseRelease,
    MouseClick,
    MouseMove,
    MouseEnter,
    MouseLeave,
    MouseWheel,

};


enum class MouseButton : uint8_t{
    None,
    Left,
    Middle,
    Right,
    X1,
    X2,
};

enum class CamMoves{
    MousePress,

    PanLeft3D,
    PanRight3D,
    PanForward3D,
    PanBackward3D,
    MouseRotation3D,
    MouseWheel3D,


    PanLeft2D,
    PanRight2D,
    PanUpward2D,
    PanDownward2D,
    MousePan2D,
    MouseWheel2D,


};


enum class TextHAlign { Left, Center, Right, Justify };
enum class TextVAlign { Top, Middle, Bottom, Baseline };



enum class PivotType : uint8_t
{
    None,
    Custom,
    BoundingSize
};

enum class PivotAxis : uint8_t
{
    Min,
    Mid,
    Max
};

enum class ViewType
{
    Fixed,
    Relative
};

enum class ViewMode
{
    Stretch,
    Fit,
    Fill
};



}

/// ## ----------------------------------------------------
///
namespace Qx::prv
{


enum class AppResult
{
    CONTINUE, // = SDL_APP_CONTINUE,
    SUCCESS,  // = SDL_APP_SUCCESS,
    FAILURE,  // = SDL_APP_FAILURE,
};

// enum class PropertyDirection
// {
//     Upwards,    /// ## From child to parents
//     Downwards,   /// ## From parent to children, needed for visible
//     None,
// };



enum class CanvasTarget
{
    None,
    SDLRenderer,
    SDLSurface,
    SDLTexture,
    GoolgeFilament
};

enum class CanvasShapeType
{
    Rect,   /// ## Needs 4
    RRect,  /// ## Needs 8: 4+4
    Circle, /// ## Needs 3: x,y,rad
    Path,   /// Dynamic
    Text,   /// Dynamic
    Image,  /// Dynamic
    Shader, /// Dynamic
};

enum class ScreenSize : uint8_t
{
    None,
    Desktop,
    Mobile,
    Tablet
};

enum class PropertyStates
{
    None        =  0,
    Geometry    = 1 << 1,
    Shape       = 1 << 2,
    Transfom    = 1 << 3,
    Camera      = 1 << 4,
    Material    = 1 << 5,
    Physics     = 1 << 6,

    UpdateChildren  = 1 << 7,
    Render          = 1 << 8, /// ## Render Item

    // StartedCanvas     = 1 << 9, /// ## Canvas::startCanvas has been called
};

/// ## Only used if Meta debugging is enabled
enum class MetaItemType
{
    None               = 0,
    Root               = 1 << 1,
    Test               = 1 << 2, /// ## For unit testing
    Window             = 1 << 3,

    GraphicsScene2D    = 1 << 4,
    GraphicsScene3D    = 1 << 5,
    GraphicsItem2D     = 1 << 6,
    GraphicsItem3D     = 1 << 7,

    PhysicsItem2D      = 1 << 8,
    PhysicsItem3D      = 1 << 9,


    NA                 = 1 << 10, /// ## N/A, for components, and other types


    /// ## DO NOT ADD ANY MORE TYPES
};


enum class ItemType : uint8_t
{
    None,
    Root,
    Window,

    /// ## All graphics items, should be listed after
    /// ## Order is important
    /// ##
    GraphicsItem2D,
    GraphicsItem3D,
    GraphicsScene2D,
    GraphicsScene3D,

    /// ## Should this exist
    /// ## This is like graphics item, but won't render
    TestItem,

    /// ## DO NOT ADD ANY MORE TYPES

};

enum class BackendResult
{
    SUCCESS,
    FAIL,
    /**/
};

enum class ViewType
{
    Relative,
    Absolute
};

template<typename E>
struct enable_bitmask_ops : std::false_type {};

template<>
struct enable_bitmask_ops<MetaItemType> : std::true_type {};

template<>
struct enable_bitmask_ops<PropertyStates> : std::true_type {};

template<typename E>
constexpr auto to_underlying(E e) noexcept
{
    static_assert(std::is_enum_v<E>, "E must be an enum");
    return static_cast<std::underlying_type_t<E>>(e);
}

template<typename E>
constexpr std::enable_if_t<
    std::is_enum_v<E> && enable_bitmask_ops<E>::value,
    E
    >
operator|(E a, E b) noexcept
{
    using U = std::underlying_type_t<E>;
    return static_cast<E>(
        static_cast<U>(a) | static_cast<U>(b)
        );
}

template<typename E>
constexpr std::enable_if_t<
    std::is_enum_v<E> && enable_bitmask_ops<E>::value,
    E
    >
operator&(E a, E b) noexcept
{
    using U = std::underlying_type_t<E>;
    return static_cast<E>(
        static_cast<U>(a) & static_cast<U>(b)
        );
}

template<typename E>
constexpr std::enable_if_t<
    std::is_enum_v<E> && enable_bitmask_ops<E>::value,
    E&
    >
operator|=(E& a, E b) noexcept
{
    a = a | b;
    return a;
}

template<typename E>
constexpr std::enable_if_t<
    std::is_enum_v<E> && enable_bitmask_ops<E>::value,
    E&
    >
operator&=(E& a, E b) noexcept
{
    a = a & b;
    return a;
}

template<typename E>
constexpr bool has_any(E value, E flags) noexcept
{
    return (to_underlying(value) & to_underlying(flags)) != 0;
}

// template<typename E>
// constexpr bool has_all(E value, E flags) noexcept
// {
//     return (to_underlying(value) & to_underlying(flags))
//     ==  to_underlying(flags);
// }


}
#endif // FLAGS_H
