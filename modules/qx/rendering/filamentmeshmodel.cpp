#include "filamentmeshmodel.h"

#include <misc/assets.h>

#include <filament/TransformManager.h>


namespace Qx {


FilamentMeshModel::FilamentMeshModel()
{

}

FilamentMeshModel::~FilamentMeshModel()
{

}

void FilamentMeshModel::clearBackendBuffers()
{
    resetEntity();
    resetMaterial();
    resetVertexBuffers();
    resetIndexBuffer();
}

void FilamentMeshModel::renderModel(filament::Engine *eng, filament::Scene *scn)
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

void FilamentMeshModel::updateVertexBuffer()
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

void FilamentMeshModel::updateIndexBuffer()
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

void FilamentMeshModel::updateMaterial()
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

void FilamentMeshModel::updateEntity()
{
    const auto validEntity = m_filamentEngine->getEntityManager().isAlive(m_filamentEntity);
    if( !validEntity )
        buildEntity();
    renderEntity();
}


void FilamentMeshModel::buildVertexBuffers()
{
    increaseTracker(m_vertexBuildsTracker);
    /// ## How many buffers (or slots)
    auto buffersCnt = vertexBuffersCount();



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

void FilamentMeshModel::setVertexBuffers()
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

void FilamentMeshModel::resetVertexBuffers()
{
    resetEntity();
    if( !m_filamentEngine || !m_filamentVertexBuffer )
        return;
    m_filamentEngine->destroy( m_filamentVertexBuffer );
    m_filamentVertexBuffer = nullptr;
}

void FilamentMeshModel::buildIndexBuffer()
{
    increaseTracker(m_indexBuildsTracker);
    m_filamentIndexBuffer = filament::IndexBuffer::Builder()
                                .indexCount(m_indexCounter)
                                .bufferType(filament::IndexBuffer::IndexType::USHORT)
                                .build(*m_filamentEngine);
}

void FilamentMeshModel::setIndexBuffer()
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

void FilamentMeshModel::resetIndexBuffer()
{
    resetEntity();
    if( !m_filamentEngine || !m_filamentIndexBuffer )
        return;
    m_filamentEngine->destroy( m_filamentIndexBuffer );
    m_filamentIndexBuffer = nullptr;
}

void FilamentMeshModel::buildMaterial()
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

void FilamentMeshModel::resetMaterial()
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

void FilamentMeshModel::buildEntity()
{
    increaseTracker(m_entityBuildsTracker);
    const auto invldBox = aabb.min == x_vector3{} &&
                          aabb.max == x_vector3{};
    dbg_assert( !invldBox ) << "Bounding box can't be {0}";
    dbg_assert( primitiveType != v_primitive::None ) << "v_primitive can't be none ....";
    m_filamentEntity = utils::EntityManager::get().create();
}

void FilamentMeshModel::resetEntity()
{
    if( !m_filamentEngine )
        return;
    if( !m_filamentEngine->getEntityManager().isAlive(m_filamentEntity) )
        return;

    m_filamentEngine->destroy( m_filamentEntity );
    m_filamentEntity.clear();
}

void FilamentMeshModel::renderEntity()
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
        const auto filamentMatrix = convertMatrix(m_transform);
        tcm.setTransform(instance, filamentMatrix);
    }

    m_filamentScene->addEntity(m_filamentEntity);
}

}
