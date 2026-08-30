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
    void updateModel( GraphicsModel *graphicsModel ) override;

    void setMesh(GraphicsModel *graphicsModel);
    void copyMesh(GraphicsModel *graphicsModel);

};

}

#endif // CUBE_H
