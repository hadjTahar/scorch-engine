#include "circle.h"


namespace Qx {


Circle::Circle(CoreItem *parent):
    prv::GraphicsItem3D{ parent }
{

    m_graphicsModel->initModel( 4, 6);
    m_graphicsModel->shaderSource = ":/materials/glow.filamat";
    m_graphicsModel->shaderName   = "glow";

    // m_graphicsModel->shaderSource = ":/materials/blue.filamat";
    // m_graphicsModel->shaderName   = "blue";


    m_graphicsModel->enableIndices   = true;
    m_graphicsModel->enablePositions = true;
    m_graphicsModel->enableUVS       = true;
    m_graphicsModel->autoReset       = true;

    m_graphicsModel->aabb = {{ 0.0f,  20.0f,  .0f }, { 20.0f, 0.0f,  .0f }};
    m_graphicsModel->culling = true;
    m_graphicsModel->changed = true;
    m_graphicsModel->ready   = true;
    m_graphicsModel->primitiveType = Qx::v_primitive::Triangles;
}

Circle::~Circle()
{
}

void Circle::updateModel()
{
    auto mesh = m_graphicsModel->requestMesh( 4, 6 );

    // // Define 4 corners of a flat quad/rectangle
    mesh.copyVertexPositions(
        {
            {  0.0f, 0.0f,  100.0f }, // Bottom-Left
            {  10.f, 0.0f,  100.0f }, // Bottom-Right
            {  10.f, 10.f,  100.0f }, // Top-Right
            {  0.0f, 10.0f, 100.0f },  // Top-Left
        }
        );

    mesh.copyVertexUVs(
        {
            {  0.0f, 0.00f }, // Bottom-Left
            {  1.f,  0.00f }, // Bottom-Right
            {  1.f,  1.00f }, // Top-Right
            {  0.0f, 1.00f },  // Top-Left
        }
        );

    mesh.copyIndices(
        {
            0, 1, 2, // Triangle 1
            0, 2, 3,  // Triangle 2
        }
        );
}


}
