#include "roundedrectangle.h"

namespace Qx {


RoundedRectangle::RoundedRectangle(CoreItem *parent):
    prv::GraphicsItem2D{ parent },
    style{ *this }
{
    transform.setSize( { 150, 150} );

    style.setBorder( 3 );
    style.setColor( Qx::red() );
    style.setBorderColor( Qx::green() );
}

void RoundedRectangle::render(Canvas *canvas)
{
    const auto sz = transform.size();
    const auto rd = style.radius();
    prv::CanvasPen pen;
    pen.setColor( style.borderColor() );
    pen.setWidth( style.border() );

    prv::SolidBrush brush;
    brush.setColor( style.color() );

    canvas->setAntialias( rendering.antilalias() );

    x_rrect rrc;
    rrc.rect   = {0,0,sz.width,sz.height};
    rrc.radius = rd;


    canvas->drawRRect( rrc,
                      pen,
                      brush );

}

}
