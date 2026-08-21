#ifndef IMAGE_H
#define IMAGE_H

#include <core/graphicsitem2d.h>
#include <properties/styles.h>


namespace Qx {

class Image : public prv::GraphicsItem2D
{

    QX_META_OBJECT( "Image",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::GraphicsItem2D )
public:
    Image(CoreItem *parent);


protected:
    void render( Qx::Canvas *canvas)override;


public:
    prv::ImageStyle style;
};

}
#endif // IMAGE_H
