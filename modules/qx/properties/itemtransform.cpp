#include "itemtransform.h"

#include <core/graphicsitem.h>


namespace Qx::prv
{

void ItemTransform::updateSize()
{
    m_item->propertyChanged(PropertyStates::Geometry);
}

void ItemTransform::update()
{
    const auto chng = m_dirtyLocal || m_dirtyWorld;
    if (m_dirtyLocal)
        updateLocal();
    if (m_dirtyWorld)
        updateWorld();
    if( chng )
        m_item->propertyChanged(PropertyStates::Transfom);
}

void ItemTransform::updateLocal()
{
    // m_localMatrix = translationMat(position) *
    //               rotationMat(rotation) *
    //               scaleMat(scale);

    // m_rotation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0, 0, 1));

    // Optimized: One matrix created, then modified in place
    m_localMatrix = glm::translate(glm::mat4(1.0f), static_cast<x_vector3>(m_position));
    m_localMatrix = m_localMatrix * glm::mat4_cast( static_cast<x_quat>(m_rotation));
    m_localMatrix = glm::scale(m_localMatrix, static_cast<x_vector3>(m_scale));

    m_dirtyLocal = false;
    m_dirtyWorld = true;
}

void ItemTransform::updateWorld()
{
    // dbg_print() << m_item;
    const auto prntItm = GraphicsItem::castItem<GraphicsItem>( m_item->parentItem() );
    const x_matrix4x4 prntMat = prntItm->transform.m_worldMatrix;
    m_worldMatrix = prntMat * static_cast<x_matrix4x4>(m_localMatrix);
    m_dirtyLocal = false;
    m_dirtyWorld = false;
}



}
