#ifndef GRAPHICSSCENE3D_H
#define GRAPHICSSCENE3D_H

#include "graphicsscene.h"



namespace Qx::prv
{

class GraphicsScene3D : public prv::GraphicsScene
{

    QX_META_OBJECT( GraphicsScene3D,
                   MetaItemType::GraphicsScene3D,
                   MetaItemType::GraphicsItem3D )

public:
    GraphicsScene3D(CoreItem *parent);
    BackendResult initCanvas(WindowItem *winItm) override final;
    void renderViews(WindowItem *winItm ) override final;

protected:
};


}
#endif // GRAPHICSSCENE3D_H
