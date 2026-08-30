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


        auto filamentEng = BackendType::filamentEngine();
        auto filamentRdr = BackendType::filamentRenderer();
        auto filamentScn = m_backend->filamentScene();

        /// ## Update the models
        for (auto itm : m_items) {
            auto item3D = castItem<GraphicsItem3D, MetaItemType::GraphicsItem3D>( itm );
            const auto itmRdr = item3D->rendering;
            auto model  = item3D->graphicsModel();


            // if( model->autoReset ){
            //     model->ready = false;
            //     model->resetMeshCounters();
            // }
            item3D->updateModel( model );
            if( !model->ready )
                continue;


            model->setTransform( item3D->transform.pivotTransform() );
            if( itmRdr.ignoreCamera() ){
                dbg_warning() << "Ignore camera is not supported for 3D items...";
                /// ## We can ignore the camera by using the inverse matrix of
                /// ## the camera, but which camera,
                /// ## One solution would be, to push items with 'ignoreCamera'
                /// ## to a vector, and add an internal loop inside 'for ( auto &vw : m_views)'
                /// ## to apply the inverse matrix
            }
            /// ## Matrix transfoms are handled in ::renderModel
            model->renderModel( filamentEng, filamentScn );
        }

        GraphicsModel::printTrackers( filamentScn );




        /// ## Render the models to the views
        /// ## ---------------------------------------
        const auto res = m_backend->beginFrame() == BackendResult::SUCCESS;
        // dbg_assert( res ) << "Renderer::beginFrame failed : " << res;
        if( !res ){
            dbg_print() << "Renderer::beginFrame failed : " << res;
            return;
        }

        const auto vldSz = m_views.empty() || m_views.size() == 1;
        dbg_assert( vldSz ) << "3D only supports one GraphicsView for now";

        const auto cnt = m_views.size();
        for (auto idx = 0; idx < cnt; ++idx) {
            auto &vw = m_views[idx];
            m_backend->renderGraphicsView( vw.get(), idx );
        }
        m_backend->endFrame();
    }

    virtual void itemRegistered(GraphicsItem *itm)
    {

    }


protected:
    std::unique_ptr<BackendType> m_backend;
};


}
#endif // NEWGRAPHICSSCENE3D_H
