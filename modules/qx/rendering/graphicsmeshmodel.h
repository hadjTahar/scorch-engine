#ifndef GRAPHICSMESHMODEL_H
#define GRAPHICSMESHMODEL_H

#include <misc/meshview.h>
#include <misc/vecs.h>
#include <core/metaobject.h>




namespace Qx {



enum class v_primitive : uint8_t
{
    Points,
    Lines,
    LineStrip,
    Triangles,
    TrianglesStrip,

    None
};



namespace prv {

template <typename BackendType>
class GraphicsScene3D;

}

class GraphicsMeshModel : public prv::MetaObject
{

    QX_META_OBJECT( "GraphicsMeshModel",
                   prv::MetaItemType::NA,
                   prv::MetaItemType::NA )

public:
    GraphicsMeshModel();
    ~GraphicsMeshModel();

    template <typename BackendType>
    friend class prv::GraphicsScene3D;

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

protected:
    void clearBackendBuffers(){}

private:

    void setTransform(const x_matrix4x4 &newTransform);
    auto vertexBuffersCount();



private:

    x_count           m_maxVertices{0};
    x_count           m_maxIndices{0};
    x_count           m_vertexCounter{0};
    x_count           m_indexCounter{0};


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
        GraphicsMeshModel::m_vertexBuildsTracker   = 0;
        GraphicsMeshModel::m_vertexSetsTracker     = 0;
        GraphicsMeshModel::m_indexBuildsTracker    = 0;
        GraphicsMeshModel::m_indexSetsTracker      = 0;
        GraphicsMeshModel::m_materialBuildsTracker = 0;
        // GraphicsMeshModel::m_materialSetsTracker   = 0;
        GraphicsMeshModel::m_entityBuildsTracker   = 0;
        // GraphicsMeshModel::m_entitySetsTracker     = 0;
    }


};


}


#endif // GRAPHICSMESHMODEL_H
