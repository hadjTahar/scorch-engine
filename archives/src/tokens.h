#ifndef TOKENS_H
#define TOKENS_H

#include <misc/utils/xdefs.h>



namespace Qx {


enum class md_state
{
    Enabled, Disabled, Hovered, Focused, Pressed, Dragged,
    Released, /// ## Extra for counter ::Pressed
};


struct MDIcon
{
    // Weight, Fill, Grade, Optical size
};


/// ## Styles:
/// ## ---------------------------------------------



/// ## Style: Typography
/// ---------------------------------------------------------------------------
/// ---------------------------------------------------------------------------

struct md_typeface
{
    inline static x_real   weight_regular = 400;
    inline static x_real   weight_medium  = 400;
    inline static x_string brand          = "Roboto";
    inline static x_string plain          = "Roboto";

};


struct md_font
{

    x_string  font;
    x_real    weight;
    x_real    size;
    x_real    tracking;
    x_real    line_height;
    x_real    wght;
    x_real    grad;
    x_real    wdth;
    x_real    rond;
    x_real    opsz;
    x_real    crsv;
    x_real    slnt;
    x_real    fill;
    x_real    hexp;
};


struct md_typescale
{
    md_font large;
    md_font medium;
    md_font small;
};


/// ## Style: Motion
/// ---------------------------------------------------------------------------
/// ---------------------------------------------------------------------------


struct md_springVals
{
    x_real damping    = 1;
    x_real stiffness  = 1000;
};

struct md_springType
{
    md_springVals spatial;
    md_springVals effects;
};

struct md_spring
{
    inline static md_springType fast      = {{0.9f, 1400}, {1.f,  3800} };
    inline static md_springType defaultt  = {{0.9f,  700}, {1.f,  1600} }; /// ## Can't use default
    inline static md_springType slow      = {{0.9f,  300}, {1.f,   800} };

};

/// ##  ---------------------------------------------------------------------------
struct md_easingCtrl
{
    x_real x0 = 0;
    x_real y0 = 0;
    x_real x1 = 1;
    x_real y1 = 1;
};


struct md_easingType : md_easingCtrl /// ## inherit (x's and y's)
{
    md_easingCtrl accelerate;
    md_easingCtrl decelerate;
};

struct md_easing
{

    inline static md_easingType emphasized =  {
        {0.05f, 0.70f, 0.10f, 1.00f}, /// ## emphasized
        {0.30f, 0.00f, 0.80f, 0.15f}, /// ## emphasized.accelerate
        {0.05f, 0.70f, 0.10f, 1.00f}  /// ## emphasized.decelerate
    };

    inline static md_easingType standard =  {
        {0.20f, 0.00f, 0.00f, 1.00f}, /// ## emphasized
        {0.30f, 0.00f, 1.00f, 1.00f}, /// ## emphasized.accelerate
        {0.00f, 0.00f, 0.00f, 1.00f}   /// ## emphasized.decelerate
    };

    inline static md_easingType legacy =  {
        {0.40f, 0.00f, 0.20f, 1.00f}, /// ## emphasized
        {0.40f, 0.00f, 1.00f, 1.00f}, /// ## emphasized.accelerate
        {0.00f, 0.00f, 0.20f, 1.00f}  /// ## emphasized.decelerate
    };

    inline static md_easingCtrl linear     =  { 0, 0, 1, 1 };
};

struct md_path
{
    inline static md_easingCtrl linear  =  { 0, 0, 1, 1 };
};


struct md_duration
{
    inline static x_real short1       = 50;
    inline static x_real short2       = 100;
    inline static x_real short3       = 150;
    inline static x_real short4       = 200;
    inline static x_real medium1      = 250;
    inline static x_real medium2      = 300;
    inline static x_real medium3      = 350;
    inline static x_real medium4      = 400;
    inline static x_real long1        = 450;
    inline static x_real long2        = 500;
    inline static x_real long3        = 550;
    inline static x_real long4        = 600;
    inline static x_real extra_long1  = 700;
    inline static x_real extra_long2  = 800;
    inline static x_real extra_long3  = 900;
    inline static x_real extra_long4  = 1000;
};


/// ##  ---------------------------------------------------------------------------

struct md_motion
{
    inline static md_spring   spring;
    inline static md_easing   easing;
    inline static md_duration duration;
    inline static md_path     path;

};

/// ## Style: Shapes
/// ---------------------------------------------------------------------------
/// ---------------------------------------------------------------------------

using md_cornerArray = std::array<x_real, 4>;

struct md_cornerValue
{
    inline static x_real none                   = 0;
    inline static x_real extra_small            = 4;
    inline static x_real small                  = 8;
    inline static x_real medium                 = 12;
    inline static x_real large                  = 16;
    inline static x_real large_increased        = 20;
    inline static x_real extra_large            = 28;
    inline static x_real extra_large_increased  = 32;
    inline static x_real extra_extra_large      = 48;
};

struct md_cornerVals : public md_cornerArray
{
    md_cornerArray top;
};

struct md_cornerLargeVals : public md_cornerArray
{
    md_cornerArray top;
    md_cornerArray end;
    md_cornerArray start;
};

struct md_corner
{

    inline static md_cornerArray full                    = {-1,-1,-1,-1};
    /// ## .extra_large, .extra_large.top
    inline static md_cornerVals extra_large              = { {28,28,28,28}, {28,28,0,0} };
    /// ## .large, .large.top, .large.end, .large.start
    inline static md_cornerLargeVals large               = {{16,16,16,16}, {16,16,0,0}, {0,16,16,0}, {16,0,0,16} };
    inline static md_cornerArray medium                  = {12,12,12,12};
    inline static md_cornerArray small                   = {8,8,8,8};
    /// ## .extra_small, .extra_small.top
    inline static md_cornerVals extra_small              = { {4,4,4,4}, {4,4,0,0} };
    inline static md_cornerArray none                    = {0,0,0,0};
    inline static md_cornerArray large_increased         = {20,20,20,20};
    inline static md_cornerArray extra_large_increased   = {32,32,32,32};
    inline static md_cornerArray extra_extra_large       = {48,48,48,48};
};


struct md_shapes
{

    inline static md_corner      corner;
    inline static md_cornerValue corner_value;

};



/// ## Style: Elevations
/// ---------------------------------------------------------------------------
/// ---------------------------------------------------------------------------
struct md_elevation
{
    x_real level0 = 0;
    x_real level1 = 1;
    x_real level2 = 3;
    x_real level3 = 6;
    x_real level4 = 8;
    x_real level5 = 12;

};


/// ## Style: Colors
/// ---------------------------------------------------------------------------
/// ---------------------------------------------------------------------------

struct md_palette
{
    /// ## Primary
    /// -------------------------
    inline static Qx::x_rgba primary0    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary5    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary10   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary15   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary20   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary25   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary30   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary35   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary40   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary45   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary50   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary55   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary60   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary65   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary70   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary75   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary80   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary85   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary90   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary95   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primary100  =  static_cast<x_rgba>( 0x00FFFFFF );



    /// ## Secondary
    /// -------------------------
    inline static Qx::x_rgba secondary0    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary5    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary10   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary15   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary20   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary25   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary30   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary35   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary40   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary45   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary50   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary55   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary60   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary65   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary70   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary75   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary80   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary85   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary90   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary95   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary100  =  static_cast<x_rgba>( 0x00FFFFFF );


    /// ## Tertiaryy
    /// -------------------------
    inline static Qx::x_rgba tertiary0    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary5    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary10   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary15   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary20   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary25   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary30   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary35   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary40   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary45   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary50   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary55   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary60   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary65   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary70   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary75   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary80   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary85   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary90   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary95   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary100  =  static_cast<x_rgba>( 0x00FFFFFF );


    /// ## Neutral
    /// -------------------------
    inline static Qx::x_rgba neutral0    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral5    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral10   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral15   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral20   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral25   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral30   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral35   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral40   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral45   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral50   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral55   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral60   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral65   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral70   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral75   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral80   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral85   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral90   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral95   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral100  =  static_cast<x_rgba>( 0x00FFFFFF );

    /// ## Neutral Varian
    /// -------------------------
    inline static Qx::x_rgba neutral_variant0    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant5    =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant10   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant15   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant20   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant25   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant30   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant35   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant40   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant45   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant50   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant55   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant60   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant65   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant70   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant75   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant80   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant85   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant90   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant95   =  static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba neutral_variant100  =  static_cast<x_rgba>( 0x00FFFFFF );


};



struct md_scheme
{
    inline static Qx::x_rgba primary                 = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceTint             = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onPrimary               = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primaryContainer        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onPrimaryContainer      = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondary               = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onSecondary             = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondaryContainer      = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onSecondaryContainer    = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiary                = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onTertiary              = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiaryContainer       = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onTertiaryContainer     = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba error                   = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onError                 = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba errorContainer          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onErrorContainer        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba background              = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onBackground            = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surface                 = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onSurface               = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceVariant          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onSurfaceVariant        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba outline                 = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba outlineVariant          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba shadow                  = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba scrim                   = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba inverseSurface          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba inverseOnSurface        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba inversePrimary          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primaryFixed            = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onPrimaryFixed          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba primaryFixedDim         = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onPrimaryFixedVariant   = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondaryFixed          = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onSecondaryFixed        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba secondaryFixedDim       = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onSecondaryFixedVariant = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiaryFixed           = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onTertiaryFixed         = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba tertiaryFixedDim        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba onTertiaryFixedVariant  = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceDim              = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceBright           = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceContainerLowest  = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceContainerLow     = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceContainer        = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceContainerHigh    = static_cast<x_rgba>( 0x00FFFFFF );
    inline static Qx::x_rgba surfaceContainerHighest = static_cast<x_rgba>( 0x00FFFFFF );

};

}



#endif // TOKENS_H
