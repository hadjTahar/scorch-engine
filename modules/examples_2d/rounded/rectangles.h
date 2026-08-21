#ifndef RECTANGLES_H
#define RECTANGLES_H

#include <items/roundedrectangle.h>


/// ## ------------------------------------------------------------

class SolidRectangle : public Qx::RoundedRectangle
{

public:
    SolidRectangle(CoreItem *parent):Qx::RoundedRectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {

        canvas->setAntialias( rendering.antilalias() );
        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::SolidBrush brush;
        brush.setColor( Qx::red() );

        const auto sz = transform.size();
        Qx::x_rrect rrc;
        rrc.rect   = {0,0,sz.width,sz.height};
        rrc.radius = style.radius();
        canvas->drawRRect(rrc,
                          pen,
                          brush );
    }
};

/// ## ------------------------------------------------------------



class LinearRectangle : public Qx::RoundedRectangle
{

public:
    LinearRectangle(CoreItem *parent):Qx::RoundedRectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        canvas->setAntialias( rendering.antilalias() );

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::LinearGradient brush;
        brush.setStartColor( Qx::red(), {0, 0} );
        brush.setEndColor(   Qx::blue(), {30, 30} );

        const auto sz = transform.size();
        Qx::x_rrect rrc;
        rrc.rect   = {0,0,sz.width,sz.height};
        rrc.radius = style.radius();
        canvas->drawRRect(rrc,
                          pen,
                          brush );
    }
};

/// ## ------------------------------------------------------------


class RadialRectangle : public Qx::RoundedRectangle
{

public:
    RadialRectangle(CoreItem *parent):Qx::RoundedRectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        canvas->setAntialias( rendering.antilalias() );

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::RadialGradient brush;
        brush.addColorStop( Qx::red(), 0 );
        brush.addColorStop( Qx::yellow(), .8 );
        brush.addColorStop( Qx::blue(), 1 );
        brush.setCenter( {25,25} );
        brush.setRadius( 25 );

        const auto sz = transform.size();
        Qx::x_rrect rrc;
        rrc.rect   = {0,0,sz.width,sz.height};
        rrc.radius = style.radius();
        canvas->drawRRect(rrc,
                          pen,
                          brush );
    }
};

/// ## ------------------------------------------------------------


class ConicalRectangle : public Qx::RoundedRectangle
{

public:
    ConicalRectangle(CoreItem *parent):Qx::RoundedRectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        canvas->setAntialias( rendering.antilalias() );

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::ConicalGradient brush;

        brush.setCenter( {30,30,} );
        brush.setEndCenter( {50,50,} );
        brush.setRadius(20);
        brush.setEndRadius(50);

        brush.addColor( Qx::red(), 0 );
        brush.addColor( Qx::yellow(), .8 );
        brush.addColor( Qx::blue(), 1 );

        const auto sz = transform.size();
        Qx::x_rrect rrc;
        rrc.rect   = {0,0,sz.width,sz.height};
        rrc.radius = style.radius();
        canvas->drawRRect(rrc,
                          pen,
                          brush );
    }
};

/// ## ------------------------------------------------------------


class SweepRectangle : public Qx::RoundedRectangle
{

public:
    SweepRectangle(CoreItem *parent):Qx::RoundedRectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        canvas->setAntialias( rendering.antilalias() );

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::SweepGradient brush;
        brush.setCenter( {30,30,} );
        brush.setStartAngle( 0 );
        brush.setEndAngle( 45 );

        brush.addColor( Qx::red(), 0 );
        brush.addColor( Qx::yellow(), .8 );
        brush.addColor( Qx::blue(), 1 );

        const auto sz = transform.size();
        Qx::x_rrect rrc;
        rrc.rect   = {0,0,sz.width,sz.height};
        rrc.radius = style.radius();
        canvas->drawRRect(rrc,
                          pen,
                          brush );
    }
};



#endif // RECTANGLES_H
