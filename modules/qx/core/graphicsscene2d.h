#ifndef GRAPHICSSCENE2D_H
#define GRAPHICSSCENE2D_H

#include "graphicsscene.h"

#include <rendering/canvas.h>


namespace Qx::prv
{

class GraphicsScene2D : public prv::GraphicsScene
{

    QX_META_OBJECT( GraphicsScene2D,
                   MetaItemType::GraphicsScene2D,
                   MetaItemType::GraphicsItem2D )

public:
    GraphicsScene2D(CoreItem *parent);
    BackendResult initCanvas(GraphicsWindow *winItm) override final;

    void renderViews(GraphicsWindow *winItm ) override final;

protected:
    std::unique_ptr<Canvas>      m_canvas;

};


}
#endif // GRAPHICSSCENE2D_H
