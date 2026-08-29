#ifndef MATERIALS_H
#define MATERIALS_H

#include "tokens.h"

namespace Qx {



struct md_ref
{
    constexpr static md_palette palette = {};
};


struct md_sys
{


    /// ## Themes colors: ( can be loaded from a file )
    /// ## and set to ::color
    /// ## ---------------------------------------------
    inline static md_scheme light                   = {};
    inline static md_scheme light_medium_contrast   = {};
    inline static md_scheme light_high_contrast     = {};
    inline static md_scheme dark                    = {};
    inline static md_scheme dark_medium_contrast    = {};
    inline static md_scheme dark_high_contrast      = {};

    /// ## Styles:
    /// ## ---------------------------------------------
    /// ## Style: Colors
    inline static md_scheme color = {};

    /// ## Style: Elevation
    inline static md_elevation  elevation { 0, 1, 3, 6, 8, 12 };


    /// ## Style: Motion
    inline static md_motion motion;

    /// ## Style: Shapes
    inline static md_shapes     shape;

    /// ## Style: Typography
    /// ## Fill them from : https://m3.material.io/styles/typography/type-scale-tokens
    inline static md_typeface   typeface;


    inline static md_typescale  display  = {
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## large
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## medium
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }  /// ## small

    };
    inline static md_typescale  headline  = {
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## large
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## medium
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }  /// ## small

    };
    inline static md_typescale  title  = {
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## large
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## medium
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }  /// ## small

    };
    inline static md_typescale  body  = {
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## large
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## medium
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }  /// ## small

    };
    inline static md_typescale  label  = {
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## large
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }, /// ## medium
        { "Roboto", 400, 400, 400, 64, 400, 0, 100, 0, 57, 0, 0, 0, 0  }  /// ## small
    };
};

struct md_md
{
    md_ref ref = {};
    md_sys sys = {};
};



/// ## prv??
struct ButtonSpecs
{
    MDIcon icon;
    void test()
    {
        // int aa;
    }
};

// inline static const Qx::md_md md = {};
}
// constexpr inline static Qx::md_md const & md = Qx::md;
constexpr inline static Qx::md_md const md = {};

#endif // MATERIALS_H
