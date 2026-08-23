#ifndef RECTANGLES_H
#define RECTANGLES_H

#include <items/rectangle.h>


/// ## ------------------------------------------------------------

class SolidRectangle : public Qx::Rectangle
{

public:
    SolidRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        const auto sz = transform.size();

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::SolidBrush brush;
        brush.setColor( Qx::red() );

        canvas->setAntialias( rendering.antilalias() );
        canvas->drawRect( {0,0, sz.width, sz.height}, pen, brush );
    }
};

/// ## ------------------------------------------------------------



class LinearRectangle : public Qx::Rectangle
{

public:
    LinearRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        const auto sz = transform.size();

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::LinearGradient brush;
        brush.setStartColor( Qx::red(), {0, 0} );
        brush.setEndColor(   Qx::blue(), {30, 30} );

        canvas->setAntialias( rendering.antilalias() );
        canvas->drawRect( {0,0, sz.width, sz.height}, pen, brush );
    }
};

/// ## ------------------------------------------------------------


class RadialRectangle : public Qx::Rectangle
{

public:
    RadialRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        const auto sz = transform.size();

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::RadialGradient brush;
        brush.addColorStop( Qx::red(), 0 );
        brush.addColorStop( Qx::yellow(), .8 );
        brush.addColorStop( Qx::blue(), 1 );
        brush.setCenter( {25,25} );
        brush.setRadius( 25 );

        canvas->setAntialias( rendering.antilalias() );
        canvas->drawRect( {0,0, sz.width, sz.height}, pen, brush );
    }
};

/// ## ------------------------------------------------------------


class ConicalRectangle : public Qx::Rectangle
{

public:
    ConicalRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        const auto sz = transform.size();

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



        canvas->setAntialias( rendering.antilalias() );
        canvas->drawRect( {0,0, sz.width, sz.height}, pen, brush );
    }
};

/// ## ------------------------------------------------------------


class SweepRectangle : public Qx::Rectangle
{

public:
    SweepRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        const auto sz = transform.size();

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


        canvas->setAntialias( rendering.antilalias() );
        canvas->drawRect( {0,0, sz.width, sz.height}, pen, brush );
    }
};



#endif // RECTANGLES_H
