#include "circle.h"


namespace Qx {


Circle::Circle(CoreItem *parent):
    prv::GraphicsItem3D{ parent }
{
}

Circle::~Circle()
{
}

void Circle::updateModel(GraphicsModel *graphicsModel)
{

    graphicsModel->initModel( 4, 6);
    graphicsModel->shaderSource = ":/materials/glow.filamat";
    graphicsModel->shaderName   = "glow";

    // graphicsModel->shaderSource = ":/materials/blue.filamat";
    // graphicsModel->shaderName   = "blue";


    graphicsModel->enableIndices   = true;
    graphicsModel->enablePositions = true;
    graphicsModel->enableUVS       = true;
    graphicsModel->autoReset       = true;

    graphicsModel->aabb = {{ 0.0f,  20.0f,  .0f }, { 20.0f, 0.0f,  .0f }};
    graphicsModel->culling = true;
    graphicsModel->changed = true;
    graphicsModel->ready   = true;
    graphicsModel->primitiveType = Qx::v_primitive::Triangles;


    auto mesh = graphicsModel->requestMesh( 4, 6 );

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
