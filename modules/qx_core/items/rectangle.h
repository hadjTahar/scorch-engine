#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <core/graphicsitem2d.h>
#include <properties/styles.h>


namespace Qx {

class Rectangle : public prv::GraphicsItem2D
{
    QX_META_OBJECT( "Rectangle",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::GraphicsItem2D )

public:
    Rectangle(CoreItem *parent);

protected:
    void render(Canvas *canvas) override;

public:
    prv::RectangleStyle style;
    void World();
};

}

#endif // RECTANGLE_H
