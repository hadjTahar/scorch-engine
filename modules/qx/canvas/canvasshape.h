#ifndef CANVASSHAPE_H
#define CANVASSHAPE_H

#include "canvasbrush.h"
#include "canvaspen.h"
#include "canvaspath.h"

#include <misc/vecs.h>
#include <misc/flags.h>
#include <misc/font.h>


namespace Qx{

struct TextFormat
{
    x_rect       rect;
    Font         font;
    TextHAlign   hAlign;
    TextVAlign   vAlign;
};

}

namespace Qx::prv
{

struct CanvasShape
{
    CanvasShape(){}
    using static_dt = std::array<x_real,10>;
    CanvasShapeType type;
    bool            antiAlias;
    x_matrix4x4     matrix;
    static_dt       data;

    /// ## Irrugular shapes
    CanvasPath     path;
    x_string       text;

    /// ## Styling
    CanvasPen   pen;
    CanvasBrush brush;
    TextFormat  format;
};

}


#endif // CANVASSHAPE_H
