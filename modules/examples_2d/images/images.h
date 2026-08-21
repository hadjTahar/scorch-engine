#ifndef IMAGES_H
#define IMAGES_H

#include <items/rectangle.h>



/// ## ------------------------------------------------------------

class ImageRectangle : public Qx::Rectangle
{

public:
    ImageRectangle(CoreItem *parent):Qx::Rectangle{ parent}{}

protected:
    void render( Qx::Canvas *canvas)override
    {
        canvas->drawImage( ":/images/test.png", {200, 100} );
    }
};


#endif // IMAGES_H
