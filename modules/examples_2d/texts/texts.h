#ifndef TEXTS_H
#define TEXTS_H

#include <items/rectangle.h>



/// ## ------------------------------------------------------------

class TextRectangle : public Qx::Rectangle
{

public:
    TextRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {

        Qx::prv::CanvasPen pen;
        pen.setColor( Qx::red() );
        // pen.setWidth( style.border );
        canvas->setAntialias( rendering.antilalias() );


        Qx::prv::SolidBrush brush;
        brush.setColor( style.color() );

        canvas->setAntialias( rendering.antilalias() );
        canvas->drawRect( {0,0,100, 50 }, pen, brush );


        Qx::Font fnt;
        fnt.familyName = "Noto Sans";
        pen.setColor( Qx::black() );

        Qx::TextFormat format;
        format.rect    = {0,0,100, 50 };
        format.font    = fnt;
        format.hAlign  = Qx::TextHAlign::Left;
        format.vAlign  = Qx::TextVAlign::Top;

        canvas->drawSimpleText( "TEXT\nnew", format, pen );
    }
};


#endif // TEXTS_H
