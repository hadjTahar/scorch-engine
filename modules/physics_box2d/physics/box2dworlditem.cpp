#include "box2dworlditem.h"

namespace Qx::Box2D {

bool areMatricesEqual(const glm::mat4& m1, const glm::mat4& m2, float epsilon = 0.00001f) {
    return glm::all(glm::epsilonEqual(m1[0], m2[0], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[1], m2[1], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[2], m2[2], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[3], m2[3], epsilon));
}



WorldItem::WorldItem(CoreItem *parent):
    Rectangle{ parent},
    m_prevMat{}
{
    m_prevMat = {-1};
    auto pCmp = attach<Qx::prv::CoreComponent>();

    pCmp->process = [this](Qx::x_real )
    {
        auto &transform = this->transform;
        const auto  gPItem    = graphicsParentItem();
        const auto  parentSz  = gPItem->transform.size();
        const auto  mat       = transform.layoutsTransform();

        const auto eps  = 0.00001f;
        const auto same =
            areMatricesEqual(m_prevMat, mat, eps ) &&
            transform.size() == parentSz;

        if( same )
            return;

        transform.setSize( parentSz );
        transform.setPosition( {0, parentSz.height, 0 } );
        /// ## Dont re-use "mat", the transform may have changed
        m_prevMat      = transform.layoutsTransform();
    };
}



}
