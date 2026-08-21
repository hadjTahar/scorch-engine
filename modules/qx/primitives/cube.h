#ifndef CUBE_H
#define CUBE_H

#include <core/graphicsitem3d.h>
#include <utils/Entity.h>
#include <filament/Box.h>



namespace Qx {


class Cube final: public prv::GraphicsItem3D
{

    QX_META_OBJECT( "Cube",
                   prv::MetaItemType::GraphicsItem3D,
                   prv::MetaItemType::GraphicsItem3D )

public:
    Cube(CoreItem *parent);
    ~Cube();

protected:
    void updateModel() override;

    void setMesh();
    void copyMesh();

};

}

#endif // CUBE_H
