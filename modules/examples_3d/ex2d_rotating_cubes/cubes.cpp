#include "cubes.h"




Cubes::Cubes(CoreItem *parent):
    Qx::prv::GraphicsItem3D{ parent }
{
    /// ## 4 requests of( 8,6)
    m_graphicsModel->initModel( 4*8, 4*36 );



    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    m_graphicsModel->shaderSource = ":/materials/blue.filamat";
    m_graphicsModel->shaderName   = "blue";

    m_graphicsModel->aabb = {
        { .0f,  .0f,  .0f },  { ww,hh, dd }
    };

    m_graphicsModel->enableIndices   = true;
    m_graphicsModel->enablePositions = true;
    m_graphicsModel->enableUVS       = false;

    m_graphicsModel->culling = true;
    m_graphicsModel->changed = true;
    m_graphicsModel->ready   = true;
    m_graphicsModel->primitiveType = Qx::v_primitive::Triangles;

    m_graphicsModel->autoReset = false;
    m_graphicsModel->resetMeshCounters();
    setMesh1();
    setMesh2();
    copyMesh1();
    copyMesh2();
}

Cubes::~Cubes()
{
}

void Cubes::updateModel()
{

}

void Cubes::setMesh1()
{
    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    auto mesh = m_graphicsModel->requestMesh( 8, 36 );

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

void Cubes::setMesh2()
{
    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    auto mesh = m_graphicsModel->requestMesh( 8, 36 );

    mesh.setVertexPositionAt(0,{ 0.0f, 0.0f, 0.0f });
    mesh.setVertexPositionAt(1,{   ww, 0.0f, 0.0f });
    mesh.setVertexPositionAt(2,{   ww,   hh, 0.0f });
    mesh.setVertexPositionAt(3,{ 0.0f,   hh, 0.0f });

    mesh.setVertexPositionAt(4,{ 0.0f, 0.0f,   dd });
    mesh.setVertexPositionAt(5,{   ww, 0.0f,   dd });
    mesh.setVertexPositionAt(6,{   ww,   hh,   dd });
    mesh.setVertexPositionAt(7,{ 0.0f,   hh,   dd });

    const auto xx = 50;
    mesh.translate( {xx, xx, xx } );

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

void Cubes::copyMesh1()
{
    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    auto mesh = m_graphicsModel->requestMesh( 8, 36 );


    std::vector<Qx::x_vector3> positions ={ { 0.0f, 0.0f, 0.0f },{   ww, 0.0f, 0.0f },
        {   ww,   hh, 0.0f },{ 0.0f,   hh, 0.0f },

        { 0.0f, 0.0f,   dd },{   ww, 0.0f,   dd },
        {   ww,   hh,   dd },{ 0.0f,   hh,   dd }

    };

    mesh.copyVertexPositions( positions );
    const auto xx = 100;
    mesh.translate( {xx, xx, xx } );

    //// ## -------------------------------------------------
    std::vector<Qx::v_index> indices = {
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

void Cubes::copyMesh2()
{
    const auto sz = transform.size();
    const auto ww = sz.width;
    const auto hh = sz.height;
    const auto dd = sz.depth;

    auto mesh = m_graphicsModel->requestMesh( 8, 36 );


    std::vector<Qx::x_vector3> positions ={ { 0.0f, 0.0f, 0.0f },{   ww, 0.0f, 0.0f },
        {   ww,   hh, 0.0f },{ 0.0f,   hh, 0.0f },

        { 0.0f, 0.0f,   dd },{   ww, 0.0f,   dd },
        {   ww,   hh,   dd },{ 0.0f,   hh,   dd }

    };

    mesh.copyVertexPositions( positions );
    const auto xx = 150;
    mesh.translate( {xx, xx, xx } );

    //// ## -------------------------------------------------
    std::vector<Qx::v_index> indices = {
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

