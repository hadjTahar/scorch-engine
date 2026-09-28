#include "worlditem.h"

#include "bodyitem.h"
#include "physicscomponent.h"

#include <box2dcpp/world.h>

namespace Qx::Box2D {

bool areMatricesEqual(const glm::mat4& m1, const glm::mat4& m2, float epsilon = 0.00001f) {
    return glm::all(glm::epsilonEqual(m1[0], m2[0], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[1], m2[1], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[2], m2[2], epsilon)) &&
           glm::all(glm::epsilonEqual(m1[3], m2[3], epsilon));
}



WorldItem::WorldItem(CoreItem *parent):
    Rectangle{ parent},
    m_prevMat{},
    m_worldAxis{ 1,1,1 }
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

        const auto sz = transform.size();
        const auto sc = x_vector3{m_worldAxis.x * parentSz.width  / sz.width,
                                  m_worldAxis.y * parentSz.height / sz.height,
                                  m_worldAxis.z * 1.              / sz.depth
        };

        transform.setScale( sc );
        const x_vector3 pos{
            m_worldAxis.x >= 0? 0 : parentSz.width,
            m_worldAxis.y >= 0? 0 : parentSz.height,
            m_worldAxis.z >= 0? 0 : parentSz.depth,

        };

        transform.setPosition( pos );
        /// ## Dont re-use "mat", the transform may have changed
        m_prevMat      = transform.layoutsTransform();
    };

    m_physicsComponent = attach<PhysicsComponent>();
    m_world            = m_physicsComponent->createWorld();

    m_physicsComponent->step = [this]()
    {
        const auto &lst = childrenView();
        for ( auto &chldPtr : lst) {
            auto chldItm = castItem<BodyItem,
                                    prv::MetaItemType::PhysicsItem2D>( chldPtr.get() );
            chldItm->physics.updateGeometry();
        }
        if( step )
            step();
        // else
        //     dbg_print_st() << "NOT CALLING STEP";

    };

}

World *WorldItem::world() const
{
    return m_world;
}

x_vector3 WorldItem::worldAxis() const
{
    return m_worldAxis;
}

void WorldItem::setWorldAxis(const x_vector3 &newWorldAxis)
{
    m_worldAxis = newWorldAxis;
}



}
