#ifndef TEXT_H
#define TEXT_H

#include <core/graphicsitem2d.h>
#include <properties/styles.h>

namespace Qx {

class Text : public prv::GraphicsItem2D
{
    QX_META_OBJECT( "Text",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::GraphicsItem2D )

public:
    Text(CoreItem *parent);

protected:
    void render(Canvas *canvas)override;

public:
    prv::TextStyle style;
};

}

#endif // TEXT_H
