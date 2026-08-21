#include "image.h"

namespace Qx {

Image::Image(CoreItem *parent):
    prv::GraphicsItem2D{ parent },
    style{ *this }
{
    // style.setSource( ":/images/test.png" );
    transform.setSize( {-1, -1} );
}

void Image::render(Canvas *canvas)
{
    canvas->drawImage( style.source(), transform.size() );
}

}
