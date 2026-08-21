#include "rectangle.h"

namespace Qx {


Rectangle::Rectangle(CoreItem *parent):
    prv::GraphicsItem2D{ parent },
    style{ *this }
{
    transform.setSize( { 250, 250} );

    style.setBorder( 3 );
    style.setColor( Qx::red() );
    style.setBorderColor( Qx::green() );
}

void Rectangle::render(Canvas *canvas)
{
    const auto sz = transform.size();
    prv::CanvasPen pen;
    pen.setColor( style.borderColor() );
    pen.setWidth( style.border() );

    prv::SolidBrush brush;
    brush.setColor( style.color() );

    canvas->setAntialias( rendering.antilalias() );
    canvas->drawRect( {0,0, sz.width, sz.height}, pen, brush );

}

}
