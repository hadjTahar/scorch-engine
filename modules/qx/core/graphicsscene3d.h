#ifndef GRAPHICSSCENE3D_H
#define GRAPHICSSCENE3D_H

#include "graphicsscene.h"
#include "graphicsitem3d.h"



namespace Qx::prv
{

class GraphicsScene3D : public prv::GraphicsScene
{

    QX_META_OBJECT( GraphicsScene3D,
                   MetaItemType::GraphicsScene3D,
                   MetaItemType::GraphicsItem3D )

public:
    GraphicsScene3D(CoreItem *parent):
        GraphicsScene{ parent }
    {
        m_itemType = ItemType::GraphicsScene3D;
    }
    BackendResult initCanvas(GraphicsWindow *winItm) override final
    {
        return BackendResult::SUCCESS;
    }
    void renderViews(GraphicsWindow *winItm ) override final
    {
        auto filamentEng = GraphicsWindow::filamentEngine();
        auto filamentRdr = GraphicsWindow::filamentRenderer();
        auto filamentScn = filamentScene();

        /// ## Update the models
        for (auto itm : m_items) {
            auto item3D = castItem<GraphicsItem3D, MetaItemType::GraphicsItem3D>( itm );
            const auto itmRdr = item3D->rendering;
            auto model  = item3D->graphicsModel();
            if( !model->ready )
                continue;

            if( model->autoReset )
                model->resetMeshCounters();
            item3D->updateModel();
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
        const auto res = filamentRdr->beginFrame( winItm->filamentSwapChain() );
        // dbg_assert( res ) << "Renderer::beginFrame failed : " << res;
        if( !res ){
            dbg_print() << "Renderer::beginFrame failed : " << res;
            return;
        }
        for ( auto &vw : m_views){
            filamentRdr->render( vw->filamentView() );
            vw->applyFilamentCamera();
        }
        filamentRdr->endFrame();
    }

protected:
};


}
#endif // GRAPHICSSCENE3D_H
