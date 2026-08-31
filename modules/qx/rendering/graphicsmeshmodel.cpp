#include "graphicsmeshmodel.h"
#include <utils/EntityManager.h>
#include <glm/gtc/type_ptr.hpp>
#include <misc/assets.h>



namespace Qx {


GraphicsMeshModel::GraphicsMeshModel()
{

}

GraphicsMeshModel::~GraphicsMeshModel()
{
}

void GraphicsMeshModel::initModel(x_count maxVertices, x_count maxIndices )
{
    dbg_assert( m_maxIndices==0 && m_maxVertices==0 ) <<
        "Model already init, can't init more than once...";


    m_maxIndices  = maxIndices;
    m_maxVertices = maxVertices;
}

void GraphicsMeshModel::resetMeshCounters()
{

    dbg_assert( m_maxIndices!=0 && m_maxVertices!=0 ) <<
        "Model is not init, call 'GraphicsMeshModel::initModel' once";

    if( enableIndices && m_indexPool.size() != m_maxIndices )
        m_indexPool.reserve( m_maxIndices );

    if( enablePositions && m_positionsPool.size() != m_maxVertices )
        m_positionsPool.reserve( m_maxVertices );
    if( enableUVS && m_uvsPool.size() != m_maxVertices )
        m_uvsPool.reserve( m_maxVertices );

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

auto GraphicsMeshModel::vertexBuffersCount()
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
