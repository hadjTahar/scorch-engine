#include "text.h"

namespace Qx {

Text::Text(CoreItem *parent):
    prv::GraphicsItem2D{ parent },
    style{ *this }
{
    style.setColor( Qx::black() );
    transform.setSize( {200,200} );
}

void Text::render(Canvas *canvas)
{
    // Qx::prv::CanvasPen pen;
    // pen.setColor( style.color() );
    // canvas->setAntialias( rendering.antilalias() );

    // Qx::Font fnt = style.font();

    // const auto sz = transform.size();
    // Qx::prv::TextFormat format;
    // format.rect    = {0,0, sz.width, sz.height };
    // format.font    = fnt;
    // format.hAlign  = style.hAlign();
    // format.vAlign  = style.vAlign();

    // canvas->drawSimpleText( style.text(), format, pen );
}


}
