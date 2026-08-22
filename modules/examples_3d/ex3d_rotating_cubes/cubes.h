#ifndef CUBES_H
#define CUBES_H

#include <core/graphicsitem3d.h>
#include <utils/Entity.h>
#include <filament/Box.h>





class Cubes final: public Qx::prv::GraphicsItem3D
{

    // QX_META_OBJECT( "Cubes",
    //                prv::MetaItemType::GraphicsItem3D,
    //                prv::MetaItemType::GraphicsItem3D )

public:
    Cubes(CoreItem *parent);
    ~Cubes();

protected:
    void updateModel() override;

    void setMesh1();
    void setMesh2();
    void copyMesh1();
    void copyMesh2();

};

#endif // CUBES_H
