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


    template <typename BackendType>
    friend class GraphicsScene3D;


public:
    GraphicsItem3D(CoreItem *parent);
    GraphicsMeshModel *graphicsMeshModel() const;

protected:
    void render(Canvas*)override final;
    void updateModel( GraphicsMeshModel * ) override{}

private:
    std::unique_ptr<GraphicsMeshModel> m_graphicsMeshModel;

};

}

#endif // GRAPHICSITEM3D_H
