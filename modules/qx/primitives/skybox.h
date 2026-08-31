#ifndef SKYBOX_H
#define SKYBOX_H

#include <core/graphicsitem3d.h>
#include <utils/Entity.h>
#include <filament/Box.h>



namespace Qx {


class SkyBox final: public prv::GraphicsItem3D
{

    QX_META_OBJECT( "SkyBox",
                   prv::MetaItemType::GraphicsItem3D,
                   prv::MetaItemType::GraphicsItem3D )

public:
    SkyBox(CoreItem *parent);
    ~SkyBox();

protected:
    void updateModel( GraphicsMeshModel *graphicsMeshModel ) override;

};

}

#endif // SKYBOX_H
