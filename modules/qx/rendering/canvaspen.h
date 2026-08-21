#ifndef CANVASPEN_H
#define CANVASPEN_H
#include <misc/vecs.h>
#include <misc/color.h>
#include <misc/debug.h>


namespace Qx::prv
{

struct DashPattern
{
    int phase;
    std::vector< float> pattern;
};

struct CanvasPen
{
    CanvasPen():
        m_width{ 1 },
        m_miter{ 1},
        m_color{ make_rgba(0,0,0,0) },
        m_dashPattern{ {} },
        m_strokeJoin{ StrokeJoin::Miter },
        m_strokeCap{ StrokeCap::Butt }
    {
    }
    enum class StrokeCap  { Butt, Round,  Square };
    enum class StrokeJoin : uint8_t{ Miter, Round,  Bevel };

    x_real      m_width;
    x_real      m_miter;
    x_rgba      m_color;
    DashPattern m_dashPattern;
    StrokeJoin  m_strokeJoin;
    StrokeCap   m_strokeCap;

public:


    inline x_rgba color() const
    {
        return m_color;
    }

    inline void setColor(const x_rgba &newColor)
    {
        m_color = newColor;
    }

    inline DashPattern dashPattern() const
    {
        return m_dashPattern;
    }

    inline void setDashPattern(const DashPattern &newPattern)
    {
        m_dashPattern = newPattern;
    }

    inline void setDashPattern(const std::vector<float> &newPattern, int offset = 0 )
    {
        m_dashPattern = {offset, newPattern};
    }

    inline StrokeJoin strokeJoin() const
    {
        return m_strokeJoin;
    }

    inline void setStrokeJoin(StrokeJoin newStrokeJoin)
    {
        m_strokeJoin = newStrokeJoin;
    }

    inline StrokeCap strokeCap() const
    {
        return m_strokeCap;
    }

    inline void setStrokeCap(StrokeCap newStrokeCap)
    {
        m_strokeCap = newStrokeCap;
    }

    inline x_real width() const
    {
        return m_width;
    }

    inline void setWidth(x_real newWidth)
    {
        m_width = newWidth;
    }

    x_real miter() const
    {
        return m_miter;
    }
    void setMiter(x_real newMiter)
    {
        m_miter = newMiter;
    }
};

}
#endif // CANVASPEN_H
