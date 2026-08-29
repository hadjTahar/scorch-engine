#ifndef NEWGRAPHICSSCENE3D_H
#define NEWGRAPHICSSCENE3D_H

#include "graphicsscene.h"
#include "graphicsitem3d.h"



namespace Qx::prv
{

template <typename BackendType>
class NewGraphicsScene3D : public prv::GraphicsScene
{

    QX_META_OBJECT( NewGraphicsScene3D,
                   MetaItemType::GraphicsScene3D,
                   MetaItemType::GraphicsItem3D )

public:
    NewGraphicsScene3D(CoreItem *parent):
        GraphicsScene{ parent }
    {
        m_itemType = ItemType::GraphicsScene3D;
    }

    BackendResult initCanvas(GraphicsWindow *winItm) override final
    {
        if( m_backend )
            return BackendResult::SUCCESS;
        m_backend = make_unique_meta<BackendType>( winItm );
        return m_backend->initBackend( winItm->properties.size() );
    }

    void renderViews(GraphicsWindow *winItm ) override final
    {

        if( !m_backend )
            return;
    }

protected:
    std::unique_ptr<BackendType>    m_backend;
};


}
#endif // NEWGRAPHICSSCENE3D_H
