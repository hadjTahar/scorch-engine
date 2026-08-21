#include "worlditem.h"

namespace Qx {

WorldItem::WorldItem(CoreItem *parent):
    Qx::prv::GraphicsItem3D{ parent },
    m_worldMin{ -100, -100, -100 },
    m_worldMax{  100,  100,  100 }
{

    m_graphicsModel->initModel( 8, 24);

    m_graphicsModel->enableIndices   = true;
    m_graphicsModel->enablePositions = true;
    m_graphicsModel->enableUVS       = false;
    m_graphicsModel->autoReset       = false;


    m_graphicsModel->shaderSource = ":/materials/wireframe.filamat";
    m_graphicsModel->shaderName   = "wireframe";
    m_graphicsModel->aabb = {
        { m_worldMin.x,  m_worldMin.y, m_worldMin.z },
        { m_worldMax.x,  m_worldMax.y, m_worldMax.z }
    };
    m_graphicsModel->culling = true;
    m_graphicsModel->changed = true;
    m_graphicsModel->ready   = true;
    m_graphicsModel->primitiveType = Qx::v_primitive::Lines;

    auto mesh = m_graphicsModel->requestMesh( 8, 24);
    mesh.copyVertexPositions(
        {
            {m_worldMin.x, m_worldMin.y, m_worldMin.z}, // 0
            {m_worldMax.x, m_worldMin.y, m_worldMin.z}, // 1
            {m_worldMax.x, m_worldMax.y, m_worldMin.z}, // 2
            {m_worldMin.x, m_worldMax.y, m_worldMin.z}, // 3
            {m_worldMin.x, m_worldMin.y, m_worldMax.z}, // 4
            {m_worldMax.x, m_worldMin.y, m_worldMax.z}, // 5
            {m_worldMax.x, m_worldMax.y, m_worldMax.z}, // 6
            {m_worldMin.x, m_worldMax.y, m_worldMax.z}  // 7
        }
        );
    mesh.copyIndices(
        {
            // Bottom square edges
            0, 1,  1, 2,  2, 3,  3, 0,
            // Top square edges
            4, 5,  5, 6,  6, 7,  7, 4,
            // Vertical connec ting edges
            0, 4,  1, 5,  2, 6,  3, 7
        });


    auto wrldCmp  =  attach<prv::CoreComponent>();
    wrldCmp->process = [this]( x_real )
    {
        updateRender();
    };

}

void WorldItem::updateModel()
{

}

x_vector3 WorldItem::worldMax() const
{
    return m_worldMax;
}

void WorldItem::setWorldMax(const x_vector3 &newWorldMax)
{
    m_worldMax = newWorldMax;
}

x_vector3 WorldItem::worldMin() const
{
    return m_worldMin;
}

void WorldItem::setWorldMin(const x_vector3 &newWorldMin)
{
    m_worldMin = newWorldMin;
}


}
