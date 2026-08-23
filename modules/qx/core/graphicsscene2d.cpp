#include "graphicsscene2d.h"
#include <glm/gtc/matrix_access.hpp> // Required header

#include "windowitem.h"

namespace Qx::prv
{


GraphicsScene2D::GraphicsScene2D(CoreItem *parent):
    GraphicsScene{ parent }
{
    m_itemType = ItemType::GraphicsScene2D;
}

BackendResult GraphicsScene2D::initCanvas(WindowItem *winItm)
{
    if( m_canvas )
        return BackendResult::SUCCESS;
    m_canvas = make_unique_meta<Canvas>( winItm->sdlWindow(), m_filamentScene );
    return m_canvas->initBackend( winItm->properties.size() );
}


void GraphicsScene2D::renderViews(WindowItem *winItm)
{

    if( !m_canvas )
        return;

    for ( auto &vwPtr : m_views)
    {
        auto vw    = vwPtr.get();
        auto cam2D = vw->camera();
        const auto gvwMatrix      = vw->transform();
        const auto camViewMatrix = cam2D->viewMatrix();
        const auto camPrjtMatrix = cam2D->projectionMatrix();
        const auto canvasMatrix  = gvwMatrix*(camPrjtMatrix * camViewMatrix);

        /// ## 2D Z sorting
        /// ---------------
        if constexpr(QX_DEF_ENABLE_2D_Z_SORTING){
            const auto camMd = cam2D->properties.mode();
            // const x_vector4 matRow{
            //     canvasMatrix[2][0],
            //     canvasMatrix[2][1],
            //     canvasMatrix[2][2],
            //     canvasMatrix[2][3]
            // };

            const auto matRow = glm::row(canvasMatrix, 2);
            /// ## Collect camera z values to avoid std::sort from re-computing them
            for ( auto itm : m_items){
                /// ## TODO: Should we ignore camera here too?
                const auto pos = itm->transform.position();
                auto depth = matRow.x * pos.z + matRow.y * pos.z +
                              matRow.z * pos.z + matRow.w;
                if( camMd == CameraMode::PERSPECTIVE )
                    depth = (matRow.w==0)? depth : depth/matRow.w;

                /// Check if parentItem() is a graphics Item?
                auto pItm = itm->parentItem();
                if( pItm->isGraphicsItem() )
                    depth += itm->graphicsParentItem()->cameraZValue();

                itm->setCameraZValue(depth);
            }

            std::sort(m_items.begin(), m_items.end(),
                      [](const GraphicsItem* a, const GraphicsItem* b)
                      {
                          auto depthA = a->cameraZValue();
                          auto depthB = b->cameraZValue();
                          return depthA > depthB;
                      });
        }

        /// ## 2D Canvas Rendering
        /// ---------------
        for ( auto itm : m_items)
        {
            auto graphicsItm      = castItem<GraphicsItem>( itm );
            const auto itmRdr     = itm->rendering;
            const auto finalMat   = graphicsItm->transform.
                                  cameraTransform( gvwMatrix, canvasMatrix, itmRdr.ignoreCamera());
            m_canvas->setMatrix( finalMat );


            graphicsItm->renderItem( m_canvas.get() );
            graphicsItm->resetPropertyStates();
        }
    }
    m_canvas->render( winItm->properties.size() );

}


}
