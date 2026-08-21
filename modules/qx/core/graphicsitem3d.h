#ifndef GRAPHICSITEM3D_H
#define GRAPHICSITEM3D_H

#include "graphicsitem.h"


namespace Qx::prv
{


class GraphicsItem3D : public prv::GraphicsItem
{
    QX_META_OBJECT( "GraphicsItem3D",
                   MetaItemType::GraphicsItem3D,
                   MetaItemType::GraphicsItem3D )

public:
    GraphicsItem3D(CoreItem *parent);
    GraphicsModel *graphicsModel() const;

protected:
    void render(Canvas*)override final;
    void updateModel() override{}

protected:
    friend class prv::GraphicsScene3D;

    std::unique_ptr<GraphicsModel> m_graphicsModel;

};

}

#endif // GRAPHICSITEM3D_H
