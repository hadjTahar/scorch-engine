#include "graphicsmeshmodel.h"
#include <utils/EntityManager.h>
#include <misc/assets.h>



namespace Qx {


GraphicsMeshModel::GraphicsMeshModel()
{
}

GraphicsMeshModel::~GraphicsMeshModel()
{
    clearBackendBuffers();
}


void GraphicsMeshModel::resize(x_count maxVertices, x_count maxIndices)
{
    if( m_maxVertices == maxVertices && m_maxIndices == maxIndices )
        return;

    m_maxIndices  = maxIndices;
    m_maxVertices = maxVertices;



    if( enableIndices && m_indexPool.size() != m_maxIndices )
        m_indexPool.resize( m_maxIndices );

    if( enablePositions && m_positionsPool.size() != m_maxVertices )
        m_positionsPool.resize( m_maxVertices );
    if( enableUVS && m_uvsPool.size() != m_maxVertices )
        m_uvsPool.resize( m_maxVertices );

    m_vertexCounter = 0;
    m_indexCounter  = 0;
}



MeshView GraphicsMeshModel::requestMesh(x_count vertexBatch,
                                      x_count indexBatch)
{
    /// ## We start from where we ended last request
    /// ## Before offsetting again
    ///
    const auto indicesOffset  = m_indexCounter;
    const auto verticesOffset = m_vertexCounter;

    m_indexCounter   += indexBatch;
    m_vertexCounter  += vertexBatch;


    if( m_indexCounter > QX_DEF_INDEX_COUNT_WARNNING )
        dbg_warning() << "Index count too large: " << m_indexCounter;

    if( m_vertexCounter > QX_DEF_VERTEX_COUNT_WARNNING )
        dbg_warning() << "Vertex count too large: " << m_vertexCounter;


    dbg_assert( m_indexCounter <= m_maxIndices )
        << "Indices requested exceeded maxIndices in ::initModel, "
           "it will cause the previous requested mesh data to be lost: "
        << m_indexCounter << " : "  << m_maxIndices;

    dbg_assert( m_vertexCounter <= m_maxVertices )
        << "Vertices requested exceeded maxVertices in ::initModel, "
           "it will cause the previous requested mesh data to be lost: "
        << m_vertexCounter << " : "  << m_maxVertices;




    const MeshView ret
    {
        m_indexPool.data(),
        m_positionsPool.data(),
        m_uvsPool.data(),
        /// ## Add rest of pools here
        /// rgba, uvData, normals, tangents

        indicesOffset,
        verticesOffset,

        indexBatch,
        vertexBatch
    };
    return ret;
}

v_count GraphicsMeshModel::vertexBuffersCount()
{
    v_count ret = 0;
    if( enablePositions && !m_positionsPool.empty() )
        ++ret;
    if( enableUVS && !m_uvsPool.empty() )
        ++ret;
    return ret;
}



void GraphicsMeshModel::setTransform(const x_matrix4x4 &newTransform)
{
    m_transform = newTransform;
}


}
