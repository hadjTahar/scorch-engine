#include "flexlayout.h"

#include <misc/flexmanager.h>
#include <glm/glm.hpp>

namespace Qx {

bool areMatricesEqual(const glm::mat4& m1, const glm::mat4& m2, float epsilon = 0.00001f) {
    return glm::all(glm::epsilonEqual(m1[0], m2[0], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[1], m2[1], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[2], m2[2], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[3], m2[3], epsilon));
}


FlexLayout::FlexLayout(CoreItem *parent):
    Rectangle{ parent},
    m_prevMat{},
    m_prevChildren{ 0 }
{

    m_prevMat = {-1};
    auto pCmp = attach<Qx::prv::CoreComponent>();

    pCmp->process = [this](Qx::x_real )
    {
              auto &transform = this->transform;
        const auto  gPItem    = graphicsParentItem();
        const auto  pSz       = gPItem->transform.size();
        const auto  mat       = transform.layoutsTransform();

        const auto eps  = 0.00001f;
        const auto same =
            areMatricesEqual(m_prevMat, mat, eps ) &&
            transform.size() == pSz;

        if( same && m_prevChildren == childrenView().size() )
            return;

        transform.setSize( pSz );
        prv::FlexManager::processFlexNodes( this );
        /// ## Dont re-use "mat", the transform may have changed
        m_prevMat      = transform.layoutsTransform();
        m_prevChildren = childrenView().size();
    };
}

}
