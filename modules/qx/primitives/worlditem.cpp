#include "worlditem.h"

namespace Qx {

WorldItem::WorldItem(CoreItem *parent):
    Qx::prv::GraphicsItem3D{ parent },
    m_worldMin{ -100, -100, -100 },
    m_worldMax{  100,  100,  100 }
{

    auto wrldCmp  =  attach<prv::CoreComponent>();
    wrldCmp->process = [this]( x_real )
    {
        updateRender();
    };

}

void WorldItem::updateModel(GraphicsMeshModel *graphicsMeshModel )
{
    if( graphicsMeshModel->ready )
        return;

    graphicsMeshModel->enableIndices   = true;
    graphicsMeshModel->enablePositions = true;
    graphicsMeshModel->enableUVS       = false;


    graphicsMeshModel->culling = true;
    graphicsMeshModel->changed = true;
    graphicsMeshModel->ready   = true;
    graphicsMeshModel->primitiveType = Qx::v_primitive::Lines;

    graphicsMeshModel->shaderSource = ":/materials/wireframe.filamat";
    graphicsMeshModel->shaderName   = "wireframe";
    graphicsMeshModel->aabb = {
        { m_worldMin.x,  m_worldMin.y, m_worldMin.z },
        { m_worldMax.x,  m_worldMax.y, m_worldMax.z }
    };

    graphicsMeshModel->resize( 8, 24);
    auto mesh = graphicsMeshModel->requestMesh( 8, 24);
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
