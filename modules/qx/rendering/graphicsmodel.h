#ifndef GRAPHICSMODEL_H
#define GRAPHICSMODEL_H

#include <misc/meshview.h>
#include <misc/vecs.h>


#include <utils/EntityManager.h>
#include <filament/Viewport.h>
#include <filament/View.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <core/metaobject.h>

#include <filament/IndexBuffer.h>
#include <filament/VertexBuffer.h>
#include <filament/RenderableManager.h>

#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/Camera.h>
#include <filament/Skybox.h>
#include <filament/Engine.h>



namespace Qx {



enum class v_primitive : uint8_t
{
    Points         = filament::RenderableManager::PrimitiveType::POINTS,
    Lines          = filament::RenderableManager::PrimitiveType::LINES,
    LineStrip      = filament::RenderableManager::PrimitiveType::LINE_STRIP,
    Triangles      = filament::RenderableManager::PrimitiveType::TRIANGLES,
    TrianglesStrip = filament::RenderableManager::PrimitiveType::TRIANGLE_STRIP,

    None,
};



namespace prv {
class GraphicsScene3D;

template <typename BackendType>
class NewGraphicsScene3D;

}

class GraphicsModel : public prv::MetaObject
{

    QX_META_OBJECT( "GraphicsModel",
                   prv::MetaItemType::NA,
                   prv::MetaItemType::NA )

public:
    GraphicsModel();
    ~GraphicsModel();

    template <typename BackendType>
    friend class prv::NewGraphicsScene3D;

public:

    x_string      shaderSource;
    x_string      shaderName;

    x_aabb  aabb{};
    bool    culling{true};
    bool    changed{true};
    /// ## false: useful for skipping transfoms, like in ECS rendering
    bool    transformable{true};
    bool    ready{false};

    /// ## true:
    /// ##     - Geometry buffers auto reset before "::updateModel" call
    /// ##     - You need to "::requestMesh" in each "::updateModel" call
    /// ##     - And update the geometry
    /// ##     - For dynamic geometry, that need changes.
    /// ## false:
    /// ##     - You must manualy call "::resetMeshCounters"
    /// ##     - Fixed-Static geometry :
    /// ##          - Either once, and "::requestMesh" once too, in the constructor.
    /// ##          - Check "rotating_cubes" and "WorldItem.cpp" examples.
    /// ##          - Basically set once and forget.
    /// ##     - Dynamic geometry:
    /// ##          - Or manualy call "::resetMeshCounters" else where.
    /// ##          - Check "ecs_rendering" example
    /// ##
    /// ## If you set it to false, and don't call "::resetMeshCounters"
    /// ## You could end up with a very large accumulating vertices counts
    /// ## While thinking you are updating the same buffers
    bool autoReset{true};



    bool enableIndices{false};
    bool enablePositions{false};
    bool enableUVS{false};
    // bool enableCOLOR{false};
    // bool enableTangents{false};

    v_primitive primitiveType {v_primitive::None};


    void initModel(x_count maxVertices, x_count maxIndices);
    void resetMeshCounters();
    MeshView requestMesh(x_count vertexBatch,
                           x_count indexBatch);


private:

    void setTransform(const x_matrix4x4 &newTransform);



    void renderModel(filament::Engine *eng, filament::Scene  *scn);
    void updateVertexBuffer();
    void updateIndexBuffer();
    void updateMaterial();
    void updateEntity();


    void clearBackendBuffers();


    auto vertexBuffersCount();
    void buildVertexBuffers();
    void setVertexBuffers();
    void resetVertexBuffers();

    void buildIndexBuffer();
    void setIndexBuffer();
    void resetIndexBuffer();

    void buildMaterial();
    void resetMaterial();

    void buildEntity();
    void resetEntity();

    void renderEntity();



private:

    x_count           m_maxVertices{0};
    x_count           m_maxIndices{0};
    x_count           m_vertexCounter{0};
    x_count           m_indexCounter{0};
    filament::Engine *m_filamentEngine{nullptr};
    filament::Scene  *m_filamentScene{nullptr};


    /// ## Model data
    utils::Entity                m_filamentEntity;
    filament::Material          *m_filamentMaterial{nullptr};
    filament::MaterialInstance  *m_filamentMaterialInstance{nullptr};
    filament::VertexBuffer      *m_filamentVertexBuffer{nullptr};
    filament::IndexBuffer       *m_filamentIndexBuffer{nullptr};



    x_matrix4x4 m_transform{1};
    v_matData   m_materialData;
    v_indices   m_indexPool;

    v_positions m_positionsPool;
    v_uvs       m_uvsPool;


    /// ## Debug trackers
    /// ## QX_DEF_3D_GEOMETRY_TRACKERS
    /// ## ------------------------------------------------------------------------------

    inline static x_count m_vertexBuildsTracker{0};
    inline static x_count m_vertexSetsTracker{0};

    inline static x_count m_indexBuildsTracker{0};
    inline static x_count m_indexSetsTracker{0};

    inline static x_count m_materialBuildsTracker{0};
    // inline static x_count m_materialSetsTracker{0};

    inline static x_count m_entityBuildsTracker{0};
    // inline static x_count m_entitySetsTracker{0};


    static inline constexpr void increaseTracker( x_count &cnt)
    {
        if( !QX_DEF_3D_GEOMETRY_TRACKERS )
            return;
        ++cnt;
    }

    static void resetDebugTrackers()
    {
        GraphicsModel::m_vertexBuildsTracker   = 0;
        GraphicsModel::m_vertexSetsTracker     = 0;
        GraphicsModel::m_indexBuildsTracker    = 0;
        GraphicsModel::m_indexSetsTracker      = 0;
        GraphicsModel::m_materialBuildsTracker = 0;
        // GraphicsModel::m_materialSetsTracker   = 0;
        GraphicsModel::m_entityBuildsTracker   = 0;
        // GraphicsModel::m_entitySetsTracker     = 0;
    }

    static void printTrackers( filament::Scene *filScn)
    {
        if( !QX_DEF_3D_GEOMETRY_TRACKERS )
            return;
        dbg_info_st() <<"--------------------------";
        dbg_info_st() <<"From start to finish";
        dbg_info_st() << "Vertex Buffer Builds: " << m_vertexBuildsTracker;
        dbg_info_st() << "Vertex Buffer Sets:   " << m_vertexSetsTracker;
        dbg_info_st() << "Index  Buffer Builds: " << m_indexBuildsTracker;
        dbg_info_st() << "Index  Buffer Sets:   " << m_indexSetsTracker;
        dbg_info_st() << "Mats   Buffer Builds: " << m_materialBuildsTracker;
        dbg_info_st() << "Entity Builds:        " << m_entityBuildsTracker;

        dbg_info_st() << "Entities count:       "  << filScn->getEntityCount();
        dbg_info_st() << "Total entities rendered: "      << filScn->getRenderableCount();
    }

};


}


#endif // GRAPHICSMODEL_H
