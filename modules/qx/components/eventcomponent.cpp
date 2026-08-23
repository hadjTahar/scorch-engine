#include "eventcomponent.h"

#include <core/graphicsscene.h>
#include <core/graphicsview.h>
#include <core/graphicscamera.h>
#include <misc/mouseevent.h>




namespace Qx::prv
{

EventComponent::EventComponent(prv::GraphicsItem *parentItem):
    CoreComponent{ parentItem },
    m_mousePolicy{ MousePolicy::CheckCapture }
{
}



bool EventComponent::checkEvent(const MouseEvent &event, prv::GraphicsScene *scn)
{
    if( m_mousePolicy == MousePolicy::AlwaysCapture )
        return true;
    // const auto matItem = m_graphicsItem->transform.pivotTransform();
    const auto xx = event.x();
    const auto yy = event.y();
    const auto zz = m_graphicsItem->transform.position().z;
    const x_vector4 eventPt = {xx,yy,zz, 1 };

    const auto &vws = scn->views();

    /// ## Test the mouse event for one m_graphicsItem
    /// ## against all the views
    for ( const auto &vwPtr : vws )
    {
        auto vw    = vwPtr.get();
        auto cam2D = vw->camera();
        const auto gvwMatrix    = vw->transform();
        const auto canvasMatrix  = ItemTransform::canvasMatrix( gvwMatrix,
                                                              cam2D->viewMatrix(),
                                                              cam2D->projectionMatrix() );

        const auto itmRdr   = m_graphicsItem->rendering;
        const auto finalMat = m_graphicsItem->transform.cameraTransform( gvwMatrix,
                                                                      canvasMatrix,
                                                                      itmRdr.ignoreCamera()
                                                                      );


        const auto pTest   = glm::inverse( finalMat) * eventPt;
        x_vector3  finalPt = pTest;
        if( pTest.w != 0 )
            finalPt = x_vector3{pTest.x/pTest.w,
                                pTest.y/pTest.w,
                                pTest.z/pTest.w};
        const auto res = m_graphicsItem->contains( finalPt );
        if( res )
            return true;
    }

    return false;
}

MousePolicy EventComponent::mousePolicy() const
{
    return m_mousePolicy;
}

void EventComponent::setMousePolicy(MousePolicy newMousePolicy)
{
    m_mousePolicy = newMousePolicy;
}

}
