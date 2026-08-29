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

        /// ## Render the models to the views
        const auto res = m_backend->beginFrame() == BackendResult::SUCCESS;
        dbg_print() << res;
        // dbg_assert( res ) << "Renderer::beginFrame failed : " << res;
        if( !res ){
            dbg_print() << "Renderer::beginFrame failed : " << res;
            return;
        }

        const auto vldSz = m_views.empty() || m_views.size() == 1;
        dbg_assert( vldSz ) << "3D only supports one GraphicsView for now";
        for ( auto &vw : m_views)
            m_backend->renderGraphicsView( vw.get() );

        m_backend->endFrame();
    }

protected:
    std::unique_ptr<BackendType>    m_backend;
};


}
#endif // NEWGRAPHICSSCENE3D_H
