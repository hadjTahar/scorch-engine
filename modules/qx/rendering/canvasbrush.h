#ifndef CANVASSTYLES_H
#define CANVASSTYLES_H

#include <misc/vecs.h>
#include <misc/color.h>
#include <misc/debug.h>

namespace Qx::prv
{

struct ColorStop
{
    x_rgba  color;
    x_real  stop;
};

struct CanvasBrush
{

    friend struct CanvasShape;
    enum class TileMode{ Clamp, Repeat , Mirror,  Decal };
    enum class BrushType{ Base, Solid, Linear, Radial, Conical, Sweep };


protected:
    CanvasBrush():
        m_type{BrushType::Base},
        m_values{},
        m_tileMode{ TileMode::Clamp }
    {
    }

public:

    auto colorStop( x_count idx ) const
    {
        dbg_assert( m_colors.size() == m_stops.size() ) << "idx is out of range";
        dbg_assert( idx < colorsCount() ) << "idx is out of range";
        return ColorStop{m_colors[ idx ], m_stops[ idx ]};
    }

    BrushType type() const
    {
        return m_type;
    }


    std::vector<x_rgba> colors() const
    {
        return m_colors;
    }

    std::vector<x_real> stops() const
    {
        return m_stops;
    }


    x_real value( x_count idx ) const
    {
        return m_values[ idx ];
    }

    TileMode tileMode() const
    {
        return m_tileMode;
    }

protected:


    x_count colorsCount() const
    {
        return m_colors.size();
    }


    std::array<x_real, 6> values() const
    {
        return m_values;
    }



protected:

    std::array< x_real,6>   m_values;
    std::vector<x_real>     m_stops;
    std::vector<x_rgba>     m_colors;
    TileMode                m_tileMode;
    BrushType               m_type;
};

/// ## ------------------------------------------------------------------------
///
struct SolidBrush : public CanvasBrush
{
    SolidBrush()
    {
        m_colors.push_back( Qx::white() );
        m_stops.push_back( 0 );
        m_type = BrushType::Solid;
    }

    x_rgba color() const
    {
        return m_colors[ 0 ];
    }

    void setColor( const x_rgba &clr)
    {
        m_colors[ 0 ] = clr;
    }
};


/// ## ------------------------------------------------------------------------
///
struct LinearGradient : public CanvasBrush
{
    LinearGradient()
    {
        m_type = BrushType::Linear;
        m_colors.push_back( Qx::white() );
        m_colors.push_back( Qx::white() );
    }
    void setStartColor( x_rgba clr, const x_vector2 &pt )
    {
        m_values[ 0 ] = pt.x;
        m_values[ 1 ] = pt.y;
        m_colors[ 0 ] = clr;
    }

    void setEndColor( x_rgba clr, const x_vector2 &pt )
    {
        m_values[ 2 ] = pt.x;
        m_values[ 3 ] = pt.y;
        m_colors[ 1 ] = clr;
    }


};



/// ## ------------------------------------------------------------------------
///
struct RadialGradient : public CanvasBrush
{
    RadialGradient() { m_type = BrushType::Radial; }
    void setCenter( const x_vector2 &ctr )
    {
        m_values[0]=ctr.x;
        m_values[1]=ctr.y;
    }
    x_vector2 center() const
    {
        return {m_values[0], m_values[1]};
    }

    void setRadius( x_real rad)
    {
        m_values[2] = rad;
    }
    x_real radius() const
    {
        return m_values[2];
    }


    void addColorStop( const x_rgba &clr, x_real stop )
    {
        m_colors.push_back( clr );
        m_stops.push_back( stop );
    }
};



/// ## ------------------------------------------------------------------------
///

struct ConicalGradient : public CanvasBrush
{
    ConicalGradient() { m_type = BrushType::Conical; }
    void setCenter( const x_vector2 &ctr )
    {
        m_values[0]=ctr.x;
        m_values[1]=ctr.y;
    }
    x_vector2 center() const
    {
        return {m_values[0], m_values[1]};
    }

    void setRadius( x_real rad)
    {
        m_values[2] = rad;
    }
    x_real radius() const
    {
        return m_values[2];
    }

    void setEndCenter( const x_vector2 &ctr )
    {
        m_values[3]=ctr.x;
        m_values[4]=ctr.y;
    }
    x_vector2 endCnter() const
    {
        return {m_values[3], m_values[4]};
    }

    void setEndRadius( x_real rad)
    {
        m_values[5] = rad;
    }
    x_real endRadius() const
    {
        return m_values[5];
    }

    void addColor( const x_rgba &clr, x_real stop )
    {
        m_colors.push_back( clr );
        // m_stops.push_back( stop );
    }
};


/// ## ------------------------------------------------------------------------
///

struct SweepGradient : public CanvasBrush
{
    SweepGradient() { m_type = BrushType::Sweep; }

    void setCenter( const x_vector2 &ctr )
    {
        m_values[0]=ctr.x;
        m_values[1]=ctr.y;
    }
    x_vector2 center() const
    {
        return {m_values[0], m_values[1]};
    }

    void setStartAngle( x_real deg)
    {
        m_values[2]=deg;
    }

    x_real startAngle() const
    {
        return m_values[2];
    }

    void setEndAngle( x_real deg)
    {
        m_values[3]=deg;
    }

    x_real endAngle() const
    {
        return m_values[3];
    }

    void addColor( const x_rgba &clr, x_real stop )
    {
        m_colors.push_back( clr );
        // m_stops.push_back( stop );
    }
};


}


/// ## ------------------------------------------------------------------------
///




#endif // CANVASSTYLES_H
