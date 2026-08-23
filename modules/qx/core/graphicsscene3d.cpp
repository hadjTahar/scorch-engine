#include "graphicsscene3d.h"

#include "graphicsitem3d.h"

#include <utils/EntityManager.h>
#include <filament/Viewport.h>
#include <filament/View.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

#include <filament/IndexBuffer.h>
#include <filament/VertexBuffer.h>
#include <filament/RenderableManager.h>

#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/Camera.h>
#include <filament/Skybox.h>
#include <filament/Engine.h>


namespace Qx::prv
{

GraphicsScene3D::GraphicsScene3D(CoreItem *parent):
    GraphicsScene{ parent }
{
    m_itemType = ItemType::GraphicsScene3D;
}

BackendResult GraphicsScene3D::initCanvas(WindowItem *winItm)
{
    return BackendResult::SUCCESS;
}


void GraphicsScene3D::renderViews(WindowItem *winItm)
{
    auto filamentEng = WindowItem::filamentEngine();
    auto filamentRdr = WindowItem::filamentRenderer();
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

}
