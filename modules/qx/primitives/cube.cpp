#include "cube.h"


namespace Qx {


Cube::Cube(CoreItem *parent):
    prv::GraphicsItem3D{ parent }
{


}

Cube::~Cube()
{
}

void Cube::updateModel(GraphicsModel *graphicsModel)
{
    /// ## Choose one
    // setMesh(graphicsModel);
    copyMesh(graphicsModel);

}

void Cube::setMesh(GraphicsModel *graphicsModel)
{
    graphicsModel->initModel( 8, 36 );
    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    graphicsModel->shaderSource = ":/materials/blue.filamat";
    graphicsModel->shaderName   = "blue";


    graphicsModel->aabb = {{ .0f,  .0f,  .0f },  { ww,hh, dd }};

    graphicsModel->enableIndices   = true;
    graphicsModel->enablePositions = true;
    graphicsModel->enableUVS       = true;
    graphicsModel->autoReset       = true;

    graphicsModel->culling = true;
    graphicsModel->changed = true;
    graphicsModel->ready   = true;
    graphicsModel->primitiveType = Qx::v_primitive::Triangles;



    auto mesh = graphicsModel->requestMesh( 8, 36 );

    mesh.setVertexPositionAt(0,{ 0.0f, 0.0f, 0.0f });
    mesh.setVertexPositionAt(1,{   ww, 0.0f, 0.0f });
    mesh.setVertexPositionAt(2,{   ww,   hh, 0.0f });
    mesh.setVertexPositionAt(3,{ 0.0f,   hh, 0.0f });

    mesh.setVertexPositionAt(4,{ 0.0f, 0.0f,   dd });
    mesh.setVertexPositionAt(5,{   ww, 0.0f,   dd });
    mesh.setVertexPositionAt(6,{   ww,   hh,   dd });
    mesh.setVertexPositionAt(7,{ 0.0f,   hh,   dd });


    // Front Face
    mesh.setIndexAt(0, 4 );
    mesh.setIndexAt(1, 5 );
    mesh.setIndexAt(2, 6 );
    mesh.setIndexAt(3, 4 );
    mesh.setIndexAt(4, 6 );
    mesh.setIndexAt(5, 7 );

    // Back Face
    mesh.setIndexAt(6, 1 );
    mesh.setIndexAt(7, 0 );
    mesh.setIndexAt(8, 3 );
    mesh.setIndexAt(9, 1 );
    mesh.setIndexAt(10, 3 );
    mesh.setIndexAt(11, 2 );


    // Left Face
    mesh.setIndexAt(12, 0 );
    mesh.setIndexAt(13, 4 );
    mesh.setIndexAt(14, 7 );
    mesh.setIndexAt(15, 0 );
    mesh.setIndexAt(16, 7 );
    mesh.setIndexAt(17, 3 );


    // Right Face
    mesh.setIndexAt(18, 5 );
    mesh.setIndexAt(19, 1 );
    mesh.setIndexAt(20, 2 );
    mesh.setIndexAt(21, 5 );
    mesh.setIndexAt(22, 2 );
    mesh.setIndexAt(23, 6 );


    // Bottom Face
    mesh.setIndexAt(24, 0 );
    mesh.setIndexAt(25, 1 );
    mesh.setIndexAt(26, 5 );
    mesh.setIndexAt(27, 0 );
    mesh.setIndexAt(28, 5 );
    mesh.setIndexAt(29, 4 );


    // Top Face
    mesh.setIndexAt(30, 3 );
    mesh.setIndexAt(31, 7 );
    mesh.setIndexAt(32, 6 );
    mesh.setIndexAt(33, 6 );
    mesh.setIndexAt(34, 6 );
    mesh.setIndexAt(35, 2 );

}

void Cube::copyMesh(GraphicsModel *graphicsModel)
{
    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    auto mesh = graphicsModel->requestMesh( 8, 36 );


    const v_positions positions ={ { 0.0f, 0.0f, 0.0f },{   ww, 0.0f, 0.0f },
        {   ww,   hh, 0.0f },{ 0.0f,   hh, 0.0f },

        { 0.0f, 0.0f,   dd },{   ww, 0.0f,   dd },
        {   ww,   hh,   dd },{ 0.0f,   hh,   dd }

    };

    mesh.copyVertexPositions( positions );


    //// ## -------------------------------------------------
    const v_indices indices = {
        // Front Face
        4, 5, 6,
        4, 6, 7,

        // Back Face
        1, 0, 3,
        1, 3, 2,

        // Left Face
        0, 4, 7,
        0, 7, 3,

        // Right Face
        5, 1, 2,
        5, 2, 6,

        // Bottom Face
        0, 1, 5,
        0, 5, 4,

        // Top Face
        3, 7, 6,
        3, 6, 2
    };

    mesh.copyIndices( indices );


}


}
