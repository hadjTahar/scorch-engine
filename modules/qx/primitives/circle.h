#ifndef CIRCLE_H
#define CIRCLE_H

#include <core/graphicsitem3d.h>
#include <utils/Entity.h>
#include <filament/Box.h>



namespace Qx {


class Circle final: public prv::GraphicsItem3D
{

    QX_META_OBJECT( "Circle",
                   prv::MetaItemType::GraphicsItem3D,
                   prv::MetaItemType::GraphicsItem3D )

public:
    Circle(CoreItem *parent);
    ~Circle();

protected:
    void updateModel(GraphicsMeshModel *graphicsMeshModel ) override;

};

}

#endif // CIRCLE_H
