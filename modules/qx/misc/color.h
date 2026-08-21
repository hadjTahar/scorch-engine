#ifndef COLOR_H
#define COLOR_H

#include <misc/defs.h>

#include <array>
#include <algorithm>
#include <cmath>


namespace Qx {



// union Color
// {

// public:

//     constexpr Color()
//     {
//         m_rgba = 0xFFFFFFFF;
//     }

//     constexpr Color( const Color &clr)
//     {
//         m_rgba = clr.m_rgba;
//     }

//     constexpr Color( const x_rgba &clr)
//     {

//         m_rgba = clr;
//     }

//     constexpr Color operator=( const Color &clr)
//     {
//         m_rgba = clr.m_rgba;
//         return *this;
//     }

//     constexpr bool operator ==( const Color &clr)
//     {
//         return false;
//     }


//     x_channel r() const{ return m_color[3];}
//     x_channel g() const{ return m_color[2];}
//     x_channel b() const{ return m_color[1];}
//     x_channel a() const{ return m_color[0];}

//     void r( x_channel vl){ m_color[3] = vl; }
//     void g( x_channel vl){ m_color[2] = vl; }
//     void b( x_channel vl){ m_color[1] = vl; }
//     void a( x_channel vl){ m_color[0] = vl; }

//     x_real nr() const{ return normalized( m_color[3] );}
//     x_real ng() const{ return normalized( m_color[2] );}
//     x_real nb() const{ return normalized( m_color[1] );}
//     x_real na() const{ return normalized( m_color[0] );}




//     x_rgba rgba() const { return m_rgba; }

// protected:
//     x_real normalized( x_channel ch ) const
//     {
//         const auto chMax    = std::numeric_limits<x_channel>::max();
//         const auto chN      = static_cast<x_real>(ch);
//         const auto chMaxN   = static_cast<x_real>(chMax);
//         return chN / chMaxN;
//     }


// private:
//     std::array<x_channel, 4> m_color;
//     x_rgba m_rgba;
// };


/// ## Cast alpha channel
inline static constexpr x_real cs( x_channel a)
{
    const auto chMax = std::numeric_limits<x_channel>::max();
    return static_cast<x_real>(a) / static_cast<x_real>(chMax);

}

inline static constexpr x_rgba make_rgba(x_channel r, x_channel g, x_channel b, x_channel a=0xFF) {

    return { cs(r),cs(g), cs(b), cs(a)};
}

/// ## Basic HTML Colors

inline static constexpr x_rgba red        (x_channel a=0xFF){ return make_rgba(0xFF, 0x00, 0x00, a); }
inline static constexpr x_rgba blue       (x_channel a=0xFF){ return make_rgba(0x00, 0x00, 0xFF, a); }
inline static constexpr x_rgba green      (x_channel a=0xFF){ return make_rgba(0x00, 0xFF, 0x00, a); }
inline static constexpr x_rgba yellow     (x_channel a=0xFF){ return make_rgba(0xFF, 0xFF, 0x00, a); }
inline static constexpr x_rgba cyan       (x_channel a=0xFF){ return make_rgba(0x00, 0xFF, 0xFF, a); }
inline static constexpr x_rgba magenta    (x_channel a=0xFF){ return make_rgba(0xFF, 0x00, 0xFF, a); }
inline static constexpr x_rgba black      (x_channel a=0xFF){ return make_rgba(0x00, 0x00, 0x00, a); }
inline static constexpr x_rgba white      (x_channel a=0xFF){ return make_rgba(0xFF, 0xFF, 0xFF, a); }
inline static constexpr x_rgba gray       (x_channel a=0xFF){ return make_rgba(0x80, 0x80, 0x80, a); }
inline static constexpr x_rgba lightGray  (x_channel a=0xFF){ return make_rgba(0xD3, 0xD3, 0xD3, a); }
inline static constexpr x_rgba darkGray   (x_channel a=0xFF){ return make_rgba(0x40, 0x40, 0x40, a); }
inline static constexpr x_rgba orange     (x_channel a=0xFF){ return make_rgba(0xFF, 0xA5, 0x00, a); }
inline static constexpr x_rgba purple     (x_channel a=0xFF){ return make_rgba(0x80, 0x00, 0x80, a); }
inline static constexpr x_rgba pink       (x_channel a=0xFF){ return make_rgba(0xFF, 0xC0, 0xCB, a); }
inline static constexpr x_rgba brown      (x_channel a=0xFF){ return make_rgba(0xA5, 0x2A, 0x2A, a); }


/// ## Extended HTML Colors
/// ## from "https://htmlcolorcodes.com/color-names/"
inline static constexpr x_rgba aliceBlue(x_channel a=0xFF)				{ return make_rgba(0xF0, 0xF8, 0xFF, a); }
inline static constexpr x_rgba antiqueWhite(x_channel a=0xFF)			{ return make_rgba(0xFA, 0xEB, 0xD7, a); }
inline static constexpr x_rgba aqua(x_channel a=0xFF)					{ return make_rgba(0x00, 0xFF, 0xFF, a); }
inline static constexpr x_rgba aquamarine(x_channel a=0xFF)				{ return make_rgba(0x7F, 0xFF, 0xD4, a); }
inline static constexpr x_rgba azure(x_channel a=0xFF)					{ return make_rgba(0xF0, 0xFF, 0xFF, a); }
inline static constexpr x_rgba beige(x_channel a=0xFF)					{ return make_rgba(0xF5, 0xF5, 0xDC, a); }
inline static constexpr x_rgba bisque(x_channel a=0xFF)					{ return make_rgba(0xFF, 0xE4, 0xC4, a); }
inline static constexpr x_rgba blanchedAlmond(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xEB, 0xCD, a); }
inline static constexpr x_rgba blueViolet(x_channel a=0xFF)				{ return make_rgba(0x8A, 0x2B, 0xE2, a); }
inline static constexpr x_rgba burlyWood(x_channel a=0xFF)				{ return make_rgba(0xDE, 0xB8, 0x87, a); }
inline static constexpr x_rgba cadetBlue(x_channel a=0xFF)				{ return make_rgba(0x5F, 0x9E, 0xA0, a); }
inline static constexpr x_rgba chartreuse(x_channel a=0xFF)				{ return make_rgba(0x7F, 0xFF, 0x00, a); }
inline static constexpr x_rgba chocolate(x_channel a=0xFF)				{ return make_rgba(0xD2, 0x69, 0x1E, a); }
inline static constexpr x_rgba coral(x_channel a=0xFF)                  { return make_rgba(0xFF, 0x7F, 0x50, a); }
inline static constexpr x_rgba cornflowerBlue(x_channel a=0xFF)			{ return make_rgba(0x64, 0x95, 0xED, a); }
inline static constexpr x_rgba cornsilk(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xF8, 0xDC, a); }
inline static constexpr x_rgba crimson(x_channel a=0xFF)				{ return make_rgba(0xDC, 0x14, 0x3C, a); }
inline static constexpr x_rgba darkBlue(x_channel a=0xFF)				{ return make_rgba(0x00, 0x00, 0x8B, a); }
inline static constexpr x_rgba darkCyan(x_channel a=0xFF)				{ return make_rgba(0x00, 0x8B, 0x8B, a); }
inline static constexpr x_rgba darkGoldenrod(x_channel a=0xFF)			{ return make_rgba(0xB8, 0x86, 0x0B, a); }
inline static constexpr x_rgba darkGreen(x_channel a=0xFF)				{ return make_rgba(0x00, 0x64, 0x00, a); }
inline static constexpr x_rgba darkKhaki(x_channel a=0xFF)				{ return make_rgba(0xBD, 0xB7, 0x6B, a); }
inline static constexpr x_rgba darkMagenta(x_channel a=0xFF)			{ return make_rgba(0x8B, 0x00, 0x8B, a); }
inline static constexpr x_rgba darkOliveGreen(x_channel a=0xFF)			{ return make_rgba(0x55, 0x6B, 0x2F, a); }
inline static constexpr x_rgba darkOrange(x_channel a=0xFF)				{ return make_rgba(0xFF, 0x8C, 0x00, a); }
inline static constexpr x_rgba darkOrchid(x_channel a=0xFF)				{ return make_rgba(0x99, 0x32, 0xCC, a); }
inline static constexpr x_rgba darkRed(x_channel a=0xFF)				{ return make_rgba(0x8B, 0x00, 0x00, a); }
inline static constexpr x_rgba darkSalmon(x_channel a=0xFF)				{ return make_rgba(0xE9, 0x96, 0x7A, a); }
inline static constexpr x_rgba darkSeaGreen(x_channel a=0xFF)			{ return make_rgba(0x8F, 0xBC, 0x8F, a); }
inline static constexpr x_rgba darkSlateBlue(x_channel a=0xFF)			{ return make_rgba(0x48, 0x3D, 0x8B, a); }
inline static constexpr x_rgba darkSlateGray(x_channel a=0xFF)			{ return make_rgba(0x2F, 0x4F, 0x4F, a); }
inline static constexpr x_rgba darkTurquoise(x_channel a=0xFF)			{ return make_rgba(0x00, 0xCE, 0xD1, a); }
inline static constexpr x_rgba darkViolet(x_channel a=0xFF)				{ return make_rgba(0x94, 0x00, 0xD3, a); }
inline static constexpr x_rgba deepPink(x_channel a=0xFF)				{ return make_rgba(0xFF, 0x14, 0x93, a); }
inline static constexpr x_rgba deepSkyBlue(x_channel a=0xFF)			{ return make_rgba(0x00, 0xBF, 0xFF, a); }
inline static constexpr x_rgba dimGray(x_channel a=0xFF)				{ return make_rgba(0x69, 0x69, 0x69, a); }
inline static constexpr x_rgba dodgerBlue(x_channel a=0xFF)				{ return make_rgba(0x1E, 0x90, 0xFF, a); }
inline static constexpr x_rgba fireBrick(x_channel a=0xFF)				{ return make_rgba(0xB2, 0x22, 0x22, a); }
inline static constexpr x_rgba floralWhite(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xFA, 0xF0, a); }
inline static constexpr x_rgba forestGreen(x_channel a=0xFF)			{ return make_rgba(0x22, 0x8B, 0x22, a); }
inline static constexpr x_rgba gainsboro(x_channel a=0xFF)				{ return make_rgba(0xDC, 0xDC, 0xDC, a); }
inline static constexpr x_rgba ghostWhite(x_channel a=0xFF)				{ return make_rgba(0xF8, 0xF8, 0xFF, a); }
inline static constexpr x_rgba gold(x_channel a=0xFF)					{ return make_rgba(0xFF, 0xD7, 0x00, a); }
inline static constexpr x_rgba goldenrod(x_channel a=0xFF)				{ return make_rgba(0xDA, 0xA5, 0x20, a); }
inline static constexpr x_rgba greenYellow(x_channel a=0xFF)			{ return make_rgba(0xAD, 0xFF, 0x2F, a); }
inline static constexpr x_rgba honeyDew(x_channel a=0xFF)				{ return make_rgba(0xF0, 0xFF, 0xF0, a); }
inline static constexpr x_rgba hotPink(x_channel a=0xFF)				{ return make_rgba(0xFF, 0x69, 0xB4, a); }
inline static constexpr x_rgba indianRed(x_channel a=0xFF)				{ return make_rgba(0xCD, 0x5C, 0x5C, a); }
inline static constexpr x_rgba indigo(x_channel a=0xFF)					{ return make_rgba(0x4B, 0x00, 0x82, a); }
inline static constexpr x_rgba ivory(x_channel a=0xFF)					{ return make_rgba(0xFF, 0xFF, 0xF0, a); }
inline static constexpr x_rgba khaki(x_channel a=0xFF)					{ return make_rgba(0xF0, 0xE6, 0x8C, a); }
inline static constexpr x_rgba lavender(x_channel a=0xFF)				{ return make_rgba(0xE6, 0xE6, 0xFA, a); }
inline static constexpr x_rgba lavenderBlush(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xF0, 0xF5, a); }
inline static constexpr x_rgba lawnGreen(x_channel a=0xFF)				{ return make_rgba(0x7C, 0xFC, 0x00, a); }
inline static constexpr x_rgba lemonChiffon(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xFA, 0xCD, a); }
inline static constexpr x_rgba lightBlue(x_channel a=0xFF)				{ return make_rgba(0xAD, 0xD8, 0xE6, a); }
inline static constexpr x_rgba lightCoral(x_channel a=0xFF)				{ return make_rgba(0xF0, 0x80, 0x80, a); }
inline static constexpr x_rgba lightCyan(x_channel a=0xFF)				{ return make_rgba(0xE0, 0xFF, 0xFF, a); }
inline static constexpr x_rgba lightGoldenRodYellow(x_channel a=0xFF)	{ return make_rgba(0xFA, 0xFA, 0xD2, a); }
inline static constexpr x_rgba lightGreen(x_channel a=0xFF)				{ return make_rgba(0x90, 0xEE, 0x90, a); }
inline static constexpr x_rgba lightPink(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xB6, 0xC1, a); }
inline static constexpr x_rgba lightSalmon(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xA0, 0x7A, a); }
inline static constexpr x_rgba lightSeaGreen(x_channel a=0xFF)			{ return make_rgba(0x20, 0xB2, 0xAA, a); }
inline static constexpr x_rgba lightSkyBlue(x_channel a=0xFF)			{ return make_rgba(0x87, 0xCE, 0xFA, a); }
inline static constexpr x_rgba lightSlateGray(x_channel a=0xFF)			{ return make_rgba(0x7, 0x788, 0x99, a); }
inline static constexpr x_rgba lightSteelBlue(x_channel a=0xFF)			{ return make_rgba(0xB0, 0xC4, 0xDE, a); }
inline static constexpr x_rgba lightYellow(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xFF, 0xE0, a); }
inline static constexpr x_rgba lime(x_channel a=0xFF)					{ return make_rgba(0x00, 0xFF, 0x00, a); }
inline static constexpr x_rgba limeGreen(x_channel a=0xFF)				{ return make_rgba(0x32, 0xCD, 0x32, a); }
inline static constexpr x_rgba linen(x_channel a=0xFF)					{ return make_rgba(0xFA, 0xF0, 0xE6, a); }
inline static constexpr x_rgba maroon(x_channel a=0xFF)					{ return make_rgba(0x80, 0x00, 0x00, a); }
inline static constexpr x_rgba mediumAquamarine(x_channel a=0xFF)		{ return make_rgba(0x66, 0xCD, 0xAA, a); }
inline static constexpr x_rgba mediumBlue(x_channel a=0xFF)				{ return make_rgba(0x00, 0x00, 0xCD, a); }
inline static constexpr x_rgba mediumOrchid(x_channel a=0xFF)			{ return make_rgba(0xBA, 0x55, 0xD3, a); }
inline static constexpr x_rgba mediumPurple(x_channel a=0xFF)			{ return make_rgba(0x93, 0x70, 0xDB, a); }
inline static constexpr x_rgba mediumSeaGreen(x_channel a=0xFF)			{ return make_rgba(0x3C, 0xB3, 0x71, a); }
inline static constexpr x_rgba mediumSlateBlue(x_channel a=0xFF)		{ return make_rgba(0x7B, 0x68, 0xEE, a); }
inline static constexpr x_rgba mediumSpringGreen(x_channel a=0xFF)		{ return make_rgba(0x00, 0xFA, 0x9A, a); }
inline static constexpr x_rgba mediumTurquoise(x_channel a=0xFF)		{ return make_rgba(0x48, 0xD1, 0xCC, a); }
inline static constexpr x_rgba mediumVioletRed(x_channel a=0xFF)		{ return make_rgba(0xC7, 0x15, 0x85, a); }
inline static constexpr x_rgba midnightBlue(x_channel a=0xFF)			{ return make_rgba(0x19, 0x19, 0x70, a); }
inline static constexpr x_rgba mintCream(x_channel a=0xFF)				{ return make_rgba(0xF5, 0xFF, 0xFA, a); }
inline static constexpr x_rgba mistyRose(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xE4, 0xE1, a); }
inline static constexpr x_rgba moccasin(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xE4, 0xB5, a); }
inline static constexpr x_rgba navajoWhite(x_channel a=0xFF)			{ return make_rgba(0xFF, 0xDE, 0xAD, a); }
inline static constexpr x_rgba navy(x_channel a=0xFF)					{ return make_rgba(0x00, 0x00, 0x80, a); }
inline static constexpr x_rgba oldLace(x_channel a=0xFF)				{ return make_rgba(0xFD, 0xF5, 0xE6, a); }
inline static constexpr x_rgba olive(x_channel a=0xFF)					{ return make_rgba(0x80, 0x80, 0x00, a); }
inline static constexpr x_rgba oliveDrab(x_channel a=0xFF)				{ return make_rgba(0x6B, 0x8E, 0x23, a); }
inline static constexpr x_rgba orchid(x_channel a=0xFF)					{ return make_rgba(0xDA, 0x70, 0xD6, a); }
inline static constexpr x_rgba paleGoldenrod(x_channel a=0xFF)			{ return make_rgba(0xEE, 0xE8, 0xAA, a); }
inline static constexpr x_rgba paleGreen(x_channel a=0xFF)				{ return make_rgba(0x98, 0xFB, 0x98, a); }
inline static constexpr x_rgba paleTurquoise(x_channel a=0xFF)			{ return make_rgba(0xAF, 0xEE, 0xEE, a); }
inline static constexpr x_rgba paleVioletRed(x_channel a=0xFF)			{ return make_rgba(0xDB, 0x70, 0x93, a); }
inline static constexpr x_rgba papayaWhip(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xEF, 0xD5, a); }
inline static constexpr x_rgba peachPuff(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xDA, 0xB9, a); }
inline static constexpr x_rgba peru(x_channel a=0xFF)					{ return make_rgba(0xCD, 0x85, 0x3F, a); }
inline static constexpr x_rgba plum(x_channel a=0xFF)					{ return make_rgba(0xDD, 0xA0, 0xDD, a); }
inline static constexpr x_rgba powderBlue(x_channel a=0xFF)				{ return make_rgba(0xB0, 0xE0, 0xE6, a); }
inline static constexpr x_rgba rosyBrown(x_channel a=0xFF)				{ return make_rgba(0xBC, 0x8F, 0x8F, a); }
inline static constexpr x_rgba royalBlue(x_channel a=0xFF)				{ return make_rgba(0x41, 0x69, 0xE1, a); }
inline static constexpr x_rgba saddleBrown(x_channel a=0xFF)			{ return make_rgba(0x8B, 0x45, 0x13, a); }
inline static constexpr x_rgba salmon(x_channel a=0xFF)					{ return make_rgba(0xFA, 0x80, 0x72, a); }
inline static constexpr x_rgba sandyBrown(x_channel a=0xFF)				{ return make_rgba(0xF4, 0xA4, 0x60, a); }
inline static constexpr x_rgba seaGreen(x_channel a=0xFF)				{ return make_rgba(0x2E, 0x8B, 0x57, a); }
inline static constexpr x_rgba seaShell(x_channel a=0xFF)				{ return make_rgba(0xFF, 0xF5, 0xEE, a); }
inline static constexpr x_rgba sienna(x_channel a=0xFF)					{ return make_rgba(0xA0, 0x52, 0x2D, a); }
inline static constexpr x_rgba silver(x_channel a=0xFF)					{ return make_rgba(0xC0, 0xC0, 0xC0, a); }
inline static constexpr x_rgba skyBlue(x_channel a=0xFF)				{ return make_rgba(0x87, 0xCE, 0xEB, a); }
inline static constexpr x_rgba slateBlue(x_channel a=0xFF)				{ return make_rgba(0x6A, 0x5A, 0xCD, a); }
inline static constexpr x_rgba slateGray(x_channel a=0xFF)				{ return make_rgba(0x70, 0x80, 0x90, a); }
inline static constexpr x_rgba snow(x_channel a=0xFF)					{ return make_rgba(0xFF, 0xFA, 0xFA, a); }
inline static constexpr x_rgba springGreen(x_channel a=0xFF)			{ return make_rgba(0x00, 0xFF, 0x7F, a); }
inline static constexpr x_rgba steelBlue(x_channel a=0xFF)				{ return make_rgba(0x46, 0x82, 0xB4, a); }
inline static constexpr x_rgba tan(x_channel a=0xFF)					{ return make_rgba(0xD2, 0xB4, 0x8C, a); }
inline static constexpr x_rgba teal(x_channel a=0xFF)					{ return make_rgba(0x00, 0x80, 0x80, a); }
inline static constexpr x_rgba thistle(x_channel a=0xFF)				{ return make_rgba(0xD8, 0xBF, 0xD8, a); }
inline static constexpr x_rgba tomato(x_channel a=0xFF)					{ return make_rgba(0xFF, 0x63, 0x47, a); }
inline static constexpr x_rgba turquoise(x_channel a=0xFF)				{ return make_rgba(0x40, 0xE0, 0xD0, a); }
inline static constexpr x_rgba violet(x_channel a=0xFF)					{ return make_rgba(0xEE, 0x82, 0xEE, a); }
inline static constexpr x_rgba wheat(x_channel a=0xFF)					{ return make_rgba(0xF5, 0xDE, 0xB3, a); }
inline static constexpr x_rgba whiteSmoke(x_channel a=0xFF)				{ return make_rgba(0xF5, 0xF5, 0xF5, a); }
inline static constexpr x_rgba yellowGreen(x_channel a=0xFF)			{ return make_rgba(0x9A, 0xCD, 0x32, a); }

/// ## ----------------------------------------------------------------------------------------------------------------
/// ## 0-1 alpha channel

/// ## Basic HTML Colors

// inline static constexpr x_rgba red        (double a){ return red( x_channel{0x00})        | Qx::cs(a) ; }
// inline static constexpr x_rgba blue       (double a){ return blue( x_channel{0x00})       | Qx::cs(a) ; }
// inline static constexpr x_rgba green      (double a){ return green( x_channel{0x00})      | Qx::cs(a) ; }
// inline static constexpr x_rgba yellow     (double a){ return yellow( x_channel{0x00})     | Qx::cs(a) ; }
// inline static constexpr x_rgba cyan       (double a){ return cyan( x_channel{0x00})       | Qx::cs(a) ; }
// inline static constexpr x_rgba magenta    (double a){ return magenta( x_channel{0x00})    | Qx::cs(a) ; }
// inline static constexpr x_rgba black      (double a){ return black( x_channel{0x00})      | Qx::cs(a) ; }
// inline static constexpr x_rgba white      (double a){ return white( x_channel{0x00})      | Qx::cs(a) ; }
// inline static constexpr x_rgba gray       (double a){ return gray( x_channel{0x00})       | Qx::cs(a) ; }
// inline static constexpr x_rgba lightGray  (double a){ return lightGray( x_channel{0x00})  | Qx::cs(a) ; }
// inline static constexpr x_rgba darkGray   (double a){ return darkGray( x_channel{0x00})   | Qx::cs(a) ; }
// inline static constexpr x_rgba orange     (double a){ return orange( x_channel{0x00})     | Qx::cs(a) ; }
// inline static constexpr x_rgba purple     (double a){ return purple( x_channel{0x00})     | Qx::cs(a) ; }
// inline static constexpr x_rgba pink       (double a){ return pink( x_channel{0x00})       | Qx::cs(a) ; }
// inline static constexpr x_rgba brown      (double a){ return brown( x_channel{0x00})      | Qx::cs(a) ; }


// inline static constexpr x_rgba aquamarine(double a)             { return aquamarine( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba azure(double a)                  { return azure( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba beige(double a)                  { return beige( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba bisque(double a)                 { return bisque( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba blanchedAlmond(double a)         { return blanchedAlmond( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba blueViolet(double a)             { return blueViolet( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba burlyWood(double a)              { return burlyWood( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba cadetBlue(double a)              { return cadetBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba chartreuse(double a)             { return chartreuse( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba chocolate(double a)              { return chocolate( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba coral(double a)                  { return coral( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba cornflowerBlue(double a)         { return cornflowerBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba cornsilk(double a)               { return cornsilk( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba crimson(double a)                { return crimson( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkBlue(double a)               { return darkBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkCyan(double a)               { return darkCyan( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkGoldenRod(double a)          { return darkGoldenRod( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkGreen(double a)              { return darkGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkKhaki(double a)              { return darkKhaki( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkMagenta(double a)            { return darkMagenta( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkOliveGreen(double a)         { return darkOliveGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkOrange(double a)             { return darkOrange( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkOrchid(double a)             { return darkOrchid( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkRed(double a)                { return darkRed( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkSalmon(double a)             { return darkSalmon( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkSeaGreen(double a)           { return darkSeaGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkSlateBlue(double a)          { return darkSlateBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkSlateGray(double a)          { return darkSlateGray( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkTurquoise(double a)          { return darkTurquoise( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba darkViolet(double a)             { return darkViolet( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba deepPink(double a)               { return deepPink( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba deepSkyBlue(double a)            { return deepSkyBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba dimGray(double a)                { return dimGray( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba dodgerBlue(double a)             { return dodgerBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba fireBrick(double a)              { return fireBrick( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba floralWhite(double a)            { return floralWhite( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba forestGreen(double a)            { return forestGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba fuchsia(double a)                { return fuchsia( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba gainsboro(double a)              { return gainsboro( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba ghostWhite(double a)             { return ghostWhite( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba gold(double a)                   { return gold( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba goldenRod(double a)              { return goldenRod( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba greenYellow(double a)            { return greenYellow( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba honeyDew(double a)               { return honeyDew( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba hotPink(double a)                { return hotPink( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba indianRed(double a)              { return indianRed( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba indigo(double a)                 { return indigo( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba ivory(double a)                  { return ivory( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba khaki(double a)                  { return khaki( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lavender(double a)               { return lavender( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lavenderBlush(double a)          { return lavenderBlush( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lawnGreen(double a)              { return lawnGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lemonChiffon(double a)           { return lemonChiffon( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightBlue(double a)              { return lightBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightCoral(double a)             { return lightCoral( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightCyan(double a)              { return lightCyan( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightGoldenRodYellow(double a)   { return lightGoldenRodYellow( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightGreen(double a)             { return lightGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightPink(double a)              { return lightPink( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightSalmon(double a)            { return lightSalmon( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightSeaGreen(double a)          { return lightSeaGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightSkyBlue(double a)           { return lightSkyBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightSlateGray(double a)         { return lightSlateGray( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightSteelBlue(double a)         { return lightSteelBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lightYellow(double a)            { return lightYellow( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba lime(double a)                   { return lime( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba limeGreen(double a)              { return limeGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba linen(double a)                  { return linen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba maroon(double a)                 { return maroon( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumAquaMarine(double a)       { return mediumAquaMarine( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumBlue(double a)             { return mediumBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumOrchid(double a)           { return mediumOrchid( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumPurple(double a)           { return mediumPurple( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumSeaGreen(double a)         { return mediumSeaGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumSlateBlue(double a)        { return mediumSlateBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumSpringGreen(double a)      { return mediumSpringGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumTurquoise(double a)        { return mediumTurquoise( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mediumVioletRed(double a)        { return mediumVioletRed( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba midnightBlue(double a)           { return midnightBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mintCream(double a)              { return mintCream( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba mistyRose(double a)              { return mistyRose( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba moccasin(double a)               { return moccasin( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba navajoWhite(double a)            { return navajoWhite( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba navy(double a)                   { return navy( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba oldLace(double a)                { return oldLace( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba olive(double a)                  { return olive( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba oliveDrab(double a)              { return oliveDrab( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba orangeRed(double a)              { return orangeRed( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba orchid(double a)                 { return orchid( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba paleGoldenRod(double a)          { return paleGoldenRod( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba paleGreen(double a)              { return paleGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba paleTurquoise(double a)          { return paleTurquoise( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba paleVioletRed(double a)          { return paleVioletRed( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba papayaWhip(double a)             { return papayaWhip( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba peachPuff(double a)              { return peachPuff( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba peru(double a)                   { return peru( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba plum(double a)                   { return plum( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba powderBlue(double a)             { return powderBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba rebeccaPurple(double a)          { return rebeccaPurple( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba rosyBrown(double a)              { return rosyBrown( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba royalBlue(double a)              { return royalBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba saddleBrown(double a)            { return saddleBrown( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba salmon(double a)                 { return salmon( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba sandyBrown(double a)             { return sandyBrown( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba seaGreen(double a)               { return seaGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba seaShell(double a)               { return seaShell( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba sienna(double a)                 { return sienna( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba silver(double a)                 { return silver( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba skyBlue(double a)                { return skyBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba slateBlue(double a)              { return slateBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba slateGray(double a)              { return slateGray( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba snow(double a)                   { return snow( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba springGreen(double a)            { return springGreen( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba steelBlue(double a)              { return steelBlue( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba tan(double a)                    { return tan( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba teal(double a)                   { return teal( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba thistle(double a)                { return thistle( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba tomato(double a)                 { return tomato( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba turquoise(double a)              { return turquoise( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba violet(double a)                 { return violet( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba wheat(double a)                  { return wheat( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba whiteSmoke(double a)             { return whiteSmoke( x_channel{0x00} ) | Qx::cs(a); }
// inline static constexpr x_rgba yellowGreen(double a)            { return yellowGreen( x_channel{0x00} ) | Qx::cs(a); }


inline static constexpr x_rgba transparent  (){ return make_rgba(0xFF, 0xFF, 0xFF, 0x00); }
inline static constexpr x_rgba clear        (){ return make_rgba(0xFF, 0xFF, 0xFF, 0xFF); }




}
#endif // COLOR_H


