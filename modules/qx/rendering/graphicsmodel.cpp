#include "graphicsmodel.h"
#include <utils/EntityManager.h>
#include <filament/TransformManager.h>
#include <glm/gtc/type_ptr.hpp>
#include <misc/assets.h>



namespace Qx {


GraphicsModel::GraphicsModel()
{

}

GraphicsModel::~GraphicsModel()
{
    clearBackendBuffers();
}

void GraphicsModel::initModel(x_count maxVertices, x_count maxIndices )
{
    dbg_assert( m_maxIndices==0 && m_maxVertices==0 ) <<
        "Model already init, can't init more than once...";
    m_maxIndices  = maxIndices;
    m_maxVertices = maxVertices;
}

void GraphicsModel::resetMeshCounters()
{

    dbg_assert( m_maxIndices!=0 && m_maxVertices!=0 ) <<
        "Model is not init, call 'GraphicsModel::initModel' once";

    if( enableIndices && m_indexPool.size() != m_maxIndices )
        m_indexPool.reserve( m_maxIndices );

    if( enablePositions && m_positionsPool.size() != m_maxVertices )
        m_positionsPool.reserve( m_maxVertices );
    if( enableUVS && m_uvsPool.size() != m_maxVertices )
        m_uvsPool.reserve( m_maxVertices );

    m_vertexCounter = 0;
    m_indexCounter  = 0;
}


MeshView GraphicsModel::requestMesh(x_count vertexBatch,
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


    /// ## resizeIndices
    /// ## We either have no
    if( !m_filamentIndexBuffer || m_filamentIndexBuffer->getIndexCount() < m_maxIndices ){
        m_indexPool.resize(enableIndices? m_indexCounter : 0);
        resetIndexBuffer();
    }
    /// ## resizeVertices
    if( !m_filamentVertexBuffer || m_filamentVertexBuffer->getVertexCount() < m_maxVertices ){
        m_positionsPool.resize( enablePositions? m_vertexCounter : 0 );
        m_uvsPool.resize( enableUVS? m_vertexCounter : 0  );
        resetVertexBuffers();
    }


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



void GraphicsModel::renderModel(filament::Engine *eng, filament::Scene *scn)
{

    m_filamentEngine = eng;
    m_filamentScene  = scn;

    /// ## We can have a model with no shader ?????

    const x_string msg =  "are enabled and can't be null, "
                         "probably ::requestMesh is not called after being enabled";
    if( enableIndices )
        dbg_assert( !m_indexPool.empty() ) << "Vertex indices " << msg;

    if( enablePositions )
        dbg_assert( !m_positionsPool.empty() ) << "Vertex positions " << msg;

    if( enableUVS )
        dbg_assert( !m_uvsPool.empty() ) << "Vertex uvs " << msg;



    updateVertexBuffer();
    updateIndexBuffer();
    updateMaterial();
    updateEntity();

}

void GraphicsModel::updateVertexBuffer()
{
    /// ## This works (sameVerticesCount) under the assumption that
    /// ## the address of the std::vector, stays the same if no size changed
    /// ## No size changed -> No capacity changed -> No address changed
    ///
    /// ## If the std::vector::size:
    /// ##      1 - Does not change: the data pointer did not change, we have the same address
    /// ##      2 - Changes        : the data pointer (might) have changed, we could be using a dead address
    ///
    const auto sameVerticesCount = m_filamentVertexBuffer &&
                                   m_vertexCounter == m_filamentVertexBuffer->getVertexCount();

    if( sameVerticesCount ){
        /// ## Should I ::setBufferAt and return?
        /// ## In case, the shape changed
        // setVertexBuffers();
        // resetEntity();
        return;
    }

    /// ## We already have a vertex buffer, but size changed
    else if( m_filamentVertexBuffer )
        resetVertexBuffers();

    /// ## We don't have a vertex buffer
    if( !m_filamentVertexBuffer )
        buildVertexBuffers();

    setVertexBuffers();
}

void GraphicsModel::updateIndexBuffer()
{
    /// ## This works (sameIndices) under the assumption that
    /// ## the address of the std::vector, stays the same if no size changed
    /// ## No size changed -> No capacity changed -> No address changed
    ///
    /// ## If the std::vector::size:
    /// ##      1 - Does not change: the data pointer did not change, we have the same address
    /// ##      2 - Changes        : the data pointer (might) have changed, we could be using a dead address
    ///
    ///
    dbg_assert( (m_indexCounter%3)==0) << "indexCount must be multiple of 3 for triangles: " << m_indexCounter;

    const auto sameIndices = m_filamentIndexBuffer &&
                             m_indexCounter == m_filamentIndexBuffer->getIndexCount();
    if( sameIndices ){
        /// ## Should I ::setIndexBuffer and return?
        /// ## In case, the shape changed
        // setIndexBuffer();
        // resetEntity();
        return;
    }

    /// ## We already have an index buffer , but size changed
    else if( m_filamentIndexBuffer )
        resetIndexBuffer();

    /// ## We don't have an index buffer
    if( !m_filamentIndexBuffer )
        buildIndexBuffer();

    setIndexBuffer();
}

void GraphicsModel::updateMaterial()
{
    /// ## If the material name did not change
    /// ## we have the same material
    ///

    const auto sameMat = !m_materialData.empty() &&
                         m_filamentMaterial &&
                         shaderName == m_filamentMaterial->getName();
    if( sameMat )
        return;

    /// ## We already have a material , but name changed
    else if( m_filamentMaterial )
        resetMaterial();

    /// ## We don't have a material
    if( !m_filamentMaterial )
        buildMaterial();

    dbg_assert(m_filamentMaterial) << "Could not build material ...";
    const auto validName = shaderName == x_string{m_filamentMaterial->getName()};
    dbg_assert(validName) <<
        "Shader names mismatch, expected: " <<
        m_filamentMaterial->getName() <<
        ", instead got: " <<
        shaderName;
}

filament::math::mat4f convertMatrix(const x_matrix4x4& sourceGlmMatrix) {
    filament::math::mat4f targetMatrix;

    // Grabs raw float pointer, forcing a safe 64-byte block copy
    // without invoking Filament's multi-argument vector constructors
    const float* rawData = x_vector::value_ptr(sourceGlmMatrix);
    std::copy(rawData, rawData + 16, &targetMatrix[0].x);

    return targetMatrix;
}

void GraphicsModel::updateEntity()
{
    const auto validEntity = m_filamentEngine->getEntityManager().isAlive(m_filamentEntity);
    if( !validEntity )
        buildEntity();
    renderEntity();
}

void GraphicsModel::clearBackendBuffers()
{
    dbg_print() << "GraphicsModel::clearBackendBuffers" << std::endl;
    resetEntity();
    resetMaterial();
    resetVertexBuffers();
    resetIndexBuffer();
}

auto GraphicsModel::vertexBuffersCount()
{
    // return 1;

    v_count ret = 0;
    if( enablePositions && !m_positionsPool.empty() )
        ++ret;
    if( enableUVS && !m_uvsPool.empty() )
        ++ret;

    return ret;
}



void GraphicsModel::buildVertexBuffers()
{
    increaseTracker(m_vertexBuildsTracker);
    /// ## How many buffers (or slots)
    v_count buffersCnt = vertexBuffersCount();


    dbg_assert( buffersCnt > 0 ) << "Filament buffer count can't be 0";
    dbg_assert( buffersCnt < 9 ) << "Filament only supports 8 buffer count...";

    auto builder = filament::VertexBuffer::Builder();
    builder.vertexCount(m_vertexCounter);
    builder.bufferCount(buffersCnt);

    uint8_t currentSlot{0};
    if( enablePositions && !m_positionsPool.empty() ){
        builder.attribute(filament::VertexAttribute::POSITION,
                          currentSlot++,
                          filament::VertexBuffer::AttributeType::FLOAT3);
    }

    if( enableUVS && !m_uvsPool.empty() ){
        builder.attribute(filament::VertexAttribute::UV0,
                          currentSlot++,
                          filament::VertexBuffer::AttributeType::FLOAT2);
    }

    m_filamentVertexBuffer = builder.build(*m_filamentEngine);
}

void GraphicsModel::setVertexBuffers()
{
    uint8_t currentSlot{0};
    if( enablePositions && !m_positionsPool.empty() ){
        increaseTracker(m_vertexSetsTracker);

        /// ## Size in bytes
        const auto positionBytes = m_vertexCounter * sizeof(v_position);
        m_filamentVertexBuffer->setBufferAt(
            *m_filamentEngine,
            currentSlot++,
            filament::VertexBuffer::BufferDescriptor(
                m_positionsPool.data(), positionBytes)
            );
    }

    if( enableUVS && !m_uvsPool.empty() ){
        /// ## Size in bytes
        const auto uvsBytes = m_vertexCounter * sizeof(v_uv);
        m_filamentVertexBuffer->setBufferAt(
            *m_filamentEngine,
            currentSlot++,
            filament::VertexBuffer::BufferDescriptor(
                m_uvsPool.data(), uvsBytes)
            );
    }
}

void GraphicsModel::resetVertexBuffers()
{
    resetEntity();
    if( !m_filamentEngine || !m_filamentVertexBuffer )
        return;
    m_filamentEngine->destroy( m_filamentVertexBuffer );
    m_filamentVertexBuffer = nullptr;
}

void GraphicsModel::buildIndexBuffer()
{
    increaseTracker(m_indexBuildsTracker);
    m_filamentIndexBuffer = filament::IndexBuffer::Builder()
                                .indexCount(m_indexCounter)
                                .bufferType(filament::IndexBuffer::IndexType::USHORT)
                                .build(*m_filamentEngine);
}


void GraphicsModel::setIndexBuffer()
{
    if( !enableIndices )
        return;
    increaseTracker(m_indexSetsTracker);
    const auto indexBuffer = m_indexPool.data();
    /// ## Size in bytes
    const auto indexBytes  = m_indexCounter * sizeof(v_index);
    m_filamentIndexBuffer->setBuffer(
        *m_filamentEngine,
        filament::IndexBuffer::BufferDescriptor(indexBuffer, indexBytes )
        );
}

void GraphicsModel::resetIndexBuffer()
{
    resetEntity();
    if( !m_filamentEngine || !m_filamentIndexBuffer )
        return;
    m_filamentEngine->destroy( m_filamentIndexBuffer );
    m_filamentIndexBuffer = nullptr;
}

void GraphicsModel::buildMaterial()
{
    increaseTracker(m_materialBuildsTracker);
    if( m_materialData.empty() )
        m_materialData =
            Assets::load( shaderSource ).
            data_copy_cast<char>();

    const auto shaderBuffer      = m_materialData.data();
    const auto shaderBufferCount = m_materialData.size();
    m_filamentMaterial = filament::Material::Builder()
                             .package(shaderBuffer, shaderBufferCount)
                             .build(*m_filamentEngine);
    m_filamentMaterialInstance = m_filamentMaterial->createInstance();
}

void GraphicsModel::resetMaterial()
{
    resetEntity();
    if( !m_filamentEngine ||
        !m_filamentMaterialInstance ||
        !m_filamentMaterial )
        return;
    m_filamentEngine->destroy( m_filamentMaterialInstance  );
    m_filamentEngine->destroy( m_filamentMaterial );
    m_filamentMaterialInstance = nullptr;
    m_filamentMaterial = nullptr;
}

void GraphicsModel::buildEntity()
{
    increaseTracker(m_entityBuildsTracker);
    const auto invldBox = aabb.min == x_vector3{} &&
                          aabb.max == x_vector3{};
    dbg_assert( !invldBox ) << "Bounding box can't be {0}";
    dbg_assert( primitiveType != v_primitive::None ) << "v_primitive can't be none ....";
    m_filamentEntity = utils::EntityManager::get().create();
}


void GraphicsModel::resetEntity()
{
    if( !m_filamentEngine )
        return;
    if( !m_filamentEngine->getEntityManager().isAlive(m_filamentEntity) )
        return;

    m_filamentEngine->destroy( m_filamentEntity );
    m_filamentEntity.clear();
}

void GraphicsModel::renderEntity()
{
    /// ## How many enitities to build
    const filament::Box boundingBox{
        {aabb.min.x, aabb.min.y, aabb.min.z},
        {aabb.max.x, aabb.max.y, aabb.max.z}
    };
    const auto prmtvTp = static_cast<filament::RenderableManager::PrimitiveType>( primitiveType );
    const x_count cntCnt  = 1;

    /// ## Index of which entity to set the attributes
    /// ## less than "cntCnt"
    const x_count entIdx  = 0;

    /// ## Where to start reading from the index buffer for this entity
    /// ## TODO: Can this be used to optimize rendering????
    // const x_count offset = 0;
    filament::RenderableManager::Builder(cntCnt)
        .geometry(entIdx, prmtvTp,
                  m_filamentVertexBuffer,
                  m_filamentIndexBuffer)
        // m_filamentIndexBuffer, offset, indexCount)
        .material(entIdx, m_filamentMaterialInstance) // Your compiled .mat file instance
        .boundingBox( boundingBox ) // Defines visibility volume boundaries
        .culling(true)
        .build(*m_filamentEngine, m_filamentEntity);

    /// ## Apply transform, or not

    if(transformable){
        filament::TransformManager& tcm = m_filamentEngine->getTransformManager();
        auto instance = tcm.getInstance(m_filamentEntity);
        const filament::math::mat4f filamentMatrix = convertMatrix(m_transform);
        tcm.setTransform(instance, filamentMatrix);
    }

    m_filamentScene->addEntity(m_filamentEntity);
}

void GraphicsModel::setTransform(const x_matrix4x4 &newTransform)
{
    m_transform = newTransform;
}




}
