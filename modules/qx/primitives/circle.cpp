#include "circle.h"


namespace Qx {


Circle::Circle(CoreItem *parent):
    prv::GraphicsItem3D{ parent }
{
}

Circle::~Circle()
{
}

void Circle::updateModel(GraphicsMeshModel *graphicsMeshModel)
{

    graphicsMeshModel->initModel( 4, 6);
    graphicsMeshModel->shaderSource = ":/materials/glow.filamat";
    graphicsMeshModel->shaderName   = "glow";

    // graphicsMeshModel->shaderSource = ":/materials/blue.filamat";
    // graphicsMeshModel->shaderName   = "blue";


    graphicsMeshModel->enableIndices   = true;
    graphicsMeshModel->enablePositions = true;
    graphicsMeshModel->enableUVS       = true;
    graphicsMeshModel->autoReset       = true;

    graphicsMeshModel->aabb = {{ 0.0f,  20.0f,  .0f }, { 20.0f, 0.0f,  .0f }};
    graphicsMeshModel->culling = true;
    graphicsMeshModel->changed = true;
    graphicsMeshModel->ready   = true;
    graphicsMeshModel->primitiveType = Qx::v_primitive::Triangles;


    auto mesh = graphicsMeshModel->requestMesh( 4, 6 );

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
