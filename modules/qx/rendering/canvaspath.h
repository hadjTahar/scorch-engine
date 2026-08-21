#ifndef CANVASPATH_H
#define CANVASPATH_H

#include <misc/vecs.h>



namespace Qx::prv {

enum class PathVerb : uint8_t {
    Move,  //! 1 point
    Line,  //! 1 point
    Quad,  //! 2 points
    Conic, //! 2 points + 1 weight
    Cubic, //! 3 points
    Close, //! 0 points

    Last_Verb = Close,
};

}

namespace Qx {



class CanvasPath
{
public:
    enum class FillType : uint8_t {
        Winding,
        EvenOdd,
        InverseWinding,
        InverseEvenOdd,

        // Default = Winding,
    };

public:
    CanvasPath();
    void moveTo( const x_vector2 &pt );
    void lineTo( const x_vector2 &pt );
    void quadTo(const x_vector2 &cPt, const x_vector2 &pt);
    void conicTo(const x_vector2 &cPt, const x_vector2 &pt, x_real w);
    void cubicTo(const x_vector2 &ctr0,
                 const x_vector2 &ctr1,
                 const x_vector2 &pt);
    void closeSubpath();

private:
    std::vector<x_vector2>     m_points;
    std::vector<x_real>        m_conics;
    std::vector<prv::PathVerb> m_verbs;
    FillType                   m_fillType;
    bool m_dynamicPath;

    /// ## ------------------------- Helper APIs -------------------------
public:

    static CanvasPath roundedRect(const x_vector2 &pt, const x_vector2 &sz,
                                x_real rTopLeft, x_real rTopRight,
                                x_real rBottomRight, x_real rBottomLeft);
    bool dynamicPath() const;
    void setDynamicPath(bool newDynamicPath);

    const std::vector<x_vector2>     &points() const;
    const std::vector<x_real>        &conics() const;
    const std::vector<prv::PathVerb> &verbs() const;
    FillType fillType() const;
    void setFillType(FillType newFillType);
};


}
#endif // CANVASPATH_H
