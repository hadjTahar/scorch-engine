#ifndef ROUNDEDRECTANGLE_H
#define ROUNDEDRECTANGLE_H

#include <core/graphicsitem2d.h>
#include <properties/styles.h>


namespace Qx {

class RoundedRectangle : public prv::GraphicsItem2D
{
    QX_META_OBJECT( "RoundedRectangle",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::GraphicsItem2D )

public:
    RoundedRectangle(CoreItem *parent);

protected:
    void render(Canvas *canvas)override;

public:
    prv::RoundedRectangleStyle style;
};

}

#endif // ROUNDEDRECTANGLE_H
