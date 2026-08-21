#include "canvaspath.h"
#include <algorithm> // Required for std::min

namespace Qx {



CanvasPath::CanvasPath():
    m_fillType{ FillType::Winding },
    m_dynamicPath{ false }
{

}

void CanvasPath::moveTo(const x_vector2 &pt)
{
    m_points.push_back( pt );
    m_verbs.push_back( prv::PathVerb::Move );
}

void CanvasPath::lineTo(const x_vector2 &pt)
{
    m_points.push_back( pt );
    m_verbs.push_back( prv::PathVerb::Line );
}

void CanvasPath::quadTo(const x_vector2 &cPt, const x_vector2 &pt)
{
    m_points.push_back( cPt );
    m_points.push_back( pt );
    m_verbs.push_back( prv::PathVerb::Quad );
}

void CanvasPath::conicTo(const x_vector2 &cPt,
                         const x_vector2 &pt,
                         x_real w)
{
    m_points.push_back( cPt );
    m_points.push_back( pt );
    m_conics.push_back( w );
    m_verbs.push_back( prv::PathVerb::Conic );
}

void CanvasPath::cubicTo(const x_vector2 &ctr0,
                         const x_vector2 &ctr1,
                         const x_vector2 &pt)
{
    m_points.push_back( ctr0 );
    m_points.push_back( ctr1 );
    m_points.push_back( pt );
    m_verbs.push_back( prv::PathVerb::Cubic );
}

void CanvasPath::closeSubpath()
{
    m_verbs.push_back( prv::PathVerb::Close );
}

CanvasPath::FillType CanvasPath::fillType() const
{
    return m_fillType;
}

void CanvasPath::setFillType(FillType newFillType)
{
    m_fillType = newFillType;
}

const std::vector<x_vector2> & CanvasPath::points() const
{
    return m_points;
}

const std::vector<prv::PathVerb> &CanvasPath::verbs() const
{
    return m_verbs;
}

const std::vector<x_real> &CanvasPath::conics() const
{
    return m_conics;
}

bool CanvasPath::dynamicPath() const
{
    return m_dynamicPath;
}

void CanvasPath::setDynamicPath(bool newDynamicPath)
{
    m_dynamicPath = newDynamicPath;
}


CanvasPath CanvasPath::roundedRect(const x_vector2 &pt,
                                     const x_vector2 &sz,
                                     x_real rTopLeft,
                                     x_real rTopRight,
                                     x_real rBottomRight,
                                     x_real rBottomLeft)
{
    CanvasPath path;
    // const x_real x = pt.x;
    // const x_real y = pt.y;
    // const x_real w = sz.x;
    // const x_real h = sz.y;
    // const x_real kappa = 0.55228474983; // constant for a good approximation of a circle with Bezier curves

    // // Ensure corner radii don't exceed half the width or height of the rectangle
    // rTopLeft = std::min(rTopLeft, std::min(w * 0.5f, h * 0.5f));
    // rTopRight = std::min(rTopRight, std::min(w * 0.5f, h * 0.5f));
    // rBottomRight = std::min(rBottomRight, std::min(w * 0.5f, h * 0.5f));
    // rBottomLeft = std::min(rBottomLeft, std::min(w * 0.5f, h * 0.5f));

    // // Top-left corner
    // path.moveTo({x + rTopLeft, y});
    // if (rTopLeft > 0) {
    //     path.cubicTo({x + rTopLeft * kappa, y},
    //                  {x, y + rTopLeft * kappa},
    //                  {x, y + rTopLeft});
    // }

    // // Left side
    // path.lineTo({x, y + h - rBottomLeft});

    // // Bottom-left corner
    // if (rBottomLeft > 0) {
    //     path.cubicTo({x, y + h - rBottomLeft * kappa},
    //                  {x + rBottomLeft * kappa, y + h},
    //                  {x + rBottomLeft, y + h});
    // }

    // // Bottom side
    // path.lineTo({x + w - rBottomRight, y + h});

    // // Bottom-right corner
    // if (rBottomRight > 0) {
    //     path.cubicTo({x + w - rBottomRight * kappa, y + h},
    //                  {x + w, y + h - rBottomRight * kappa},
    //                  {x + w, y + h - rBottomRight});
    // }

    // // Right side
    // path.lineTo({x + w, y + rTopRight});

    // // Top-right corner
    // if (rTopRight > 0) {
    //     path.cubicTo({x + w, y + rTopRight * kappa},
    //                  {x + w - rTopRight * kappa, y},
    //                  {x + w - rTopRight, y});
    // }

    // // Top side
    // path.lineTo({x + rTopLeft, y});
    // path.closeSubpath();

    return path;
}

}
