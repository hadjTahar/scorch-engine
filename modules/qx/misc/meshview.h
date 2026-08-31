#ifndef MESHVIEW_H
#define MESHVIEW_H


#include "vecs.h"
#include "debugprint.h"
#include "debug.h"
#include <algorithm>


namespace Qx {

struct MeshView
{



    MeshView()
    {

    }
    ~MeshView()
    {
        /// ## Don't add any state depending logic here,
        /// ## Object can be destroyed on return, or std::vector resize
    }

    /// ## ------------------------------------------------------------------

    inline /*constexpr*/ void setVertexPositionAt( v_count idx,
                                                  const x_vector3 &pos)
    {
        checkVerticesIndex( "VertexPosition", idx );
        checkValidPointers( "VertexPosition", positionsBegin, positionsEnd );
        positionsBegin[idx] = pos;
    }

    inline /*constexpr*/ void copyVertexPositions( const v_positions &positions)
    {
        checkVertexCopySize( "VertexPositions", positions.size() );
        checkValidPointers( "VertexPosition", positionsBegin, positionsEnd );
        std::copy(positions.begin(),
                  positions.end(),
                  positionsBegin);
    }

    /// ## ------------------------------------------------------------------

    inline /*constexpr*/ void setVertexUVAt( v_count idx,
                                            const x_vector2 &uv)
    {
        checkVerticesIndex( "VertexUV", idx );
        checkValidPointers( "VertexUV", uvsBegin, uvsEnd );
        uvsBegin[idx] = uv;
    }

    inline /*constexpr*/ void copyVertexUVs( const v_uvs &uvs)
    {
        checkVertexCopySize( "VertexUV", uvs.size() );
        checkValidPointers( "VertexUV", uvsBegin, uvsEnd );
        std::copy(uvs.begin(),
                  uvs.end(),
                  uvsBegin);
    }


    /// ## ------------------------------------------------------------------


    inline /*constexpr*/ void setIndexAt(v_count idx,
                                   const v_index vIdx)
    {
        checkIndicesIndex( idx );
        checkValidPointers( "Index", indicesBegin, indicesEnd );

        /// ## Offset the "indices", to the correct vertices
        /// ## from "0" base to "verticesOffset"
        indicesBegin[idx] = vIdx+verticesOffset;
    }

    inline /*constexpr*/ void copyIndices( const v_indices &indices)
    {
        checkIndexCopySize( indices.size() );
        checkValidPointers( "Index", indicesBegin, indicesEnd );
        /// ## Offset the "indices", to the correct vertices
        /// ## from "0" base to "verticesOffset"
        const auto idxOffset = verticesOffset;
        std::ranges::transform(
            indices,
            indicesBegin,
            [idxOffset](auto value) {
                return value + idxOffset;
            }
            );
    }

    /// ## ------------------------------------------------------------------

    void translate(const x_vector3 &vec)
    {
        checkValidPointers( "VertexPosition", positionsBegin, positionsEnd );
        std::ranges::for_each(
            positionsBegin,
            positionsEnd,
            [&](x_vector3& pos) {
                pos += vec;
            }
            );
    }

    void transform( const x_matrix4x4 &mat)
    {
        dbg_warning() << "MeshView::transform is not supported yet";
        checkValidPointers( "VertexPosition", positionsBegin, positionsEnd );
    }
private:

    template<typename Type>
    auto ptr_distance(Type const*const begin, Type const*const end)
    {
        return static_cast<std::size_t>( end - begin );
    }



    inline /*constexpr*/ void checkVerticesIndex( const x_string &name,
                                                 v_count idx )
    {
        const auto cnt = verticesBatch;
        const auto vldIdx = (idx < cnt );
        dbg_loop_assert( vldIdx ) << "Vertices index of "
                           << name
                           << ", can't exceed vertexCount: "
                           << idx
                           << " : "
                           << verticesBatch;
    }

    inline /*constexpr*/ void checkIndicesIndex( v_count idx )
    {
        const auto cnt = indicesBatch;
        const auto vldIdx = (idx < cnt);
        dbg_loop_assert( vldIdx ) << "Indices index can't exceed vertexCount: "
                           << idx
                           << " : "
                           << cnt;
    }

    inline /*constexpr*/ void checkVertexCopySize(  const x_string &name,
                                                  x_count cnt )
    {
        const auto vldCnt = (cnt == verticesBatch);
        dbg_loop_assert( vldCnt ) << "Copied vertices sizes "
                           << name
                           << ", are different from requested: ( "
                           << cnt
                           << " : "
                           << verticesBatch
                           << " )";
    }


    inline /*constexpr*/ void checkIndexCopySize(x_count cnt )
    {
        const auto vldCnt = (cnt == indicesBatch);
        dbg_loop_assert( vldCnt ) << "Copied indices sizes "
                           << ", are different from requested: ( "
                           << cnt
                           << " : "
                           << indicesBatch
                           << " )";
    }


    inline /*constexpr*/ void checkValidPointers( const x_string &name,
                                                void const*const begin,
                                                void const*const end  )
    {
        /// ## Most likely it's not enabled check GraphicsMeshModel::enable___
        const auto invalid = (begin == nullptr) || (end == nullptr);
        dbg_loop_assert( !invalid )
            << "Null pointers for: "
            << name
            << " begin: " << begin
            << " end: " << end
            ;
    }


    /// ## ------------------------------------------------------------------

public:
    void printMeshInfo()
    {
        dbg_print() << "***********************************";
        dbg_print() << "positionsBegin: "   << positionsBegin;
        dbg_print() << "positionsEnd: "     << positionsEnd;
        dbg_print() << "uvsBegin: "         << uvsBegin;
        dbg_print() << "uvsEnd: "           << uvsEnd;
        dbg_print() << "indicesBegin: "     << indicesBegin;
        dbg_print() << "indicesEnd: "       << indicesEnd;


        dbg_print() << "positionsDiff: "    << positionsEnd-positionsBegin;
        dbg_print() << "uvssDiff: "         << uvsEnd-uvsBegin;
        dbg_print() << "indicesDiff: "      << indicesEnd-indicesBegin;

    }
private:
    /// ## --------------------------------------------------------
    MeshView(

        v_index    *indicesPool,

        x_vector3  *positionsPool,
        x_vector2  *uvsPool,
        /// ## Add rest of pools here
        /// rgba, uvData, normals, tangents

        x_count idxOffset,
        x_count vtxOffset,

        x_count idxBatch,
        x_count vtxBatch
        )
    {
        verticesOffset = vtxOffset;
        indicesOffset  = idxOffset;

        indicesBatch   = idxBatch;
        verticesBatch  = vtxBatch;

        if( indicesPool ){
            indicesBegin = indicesPool  + indicesOffset;
            indicesEnd   = indicesBegin + indicesBatch;
        }


        if( positionsPool ){
            positionsBegin = positionsPool  + verticesOffset;
            positionsEnd   = positionsBegin + verticesBatch;
        }

        if( uvsPool ){
            uvsBegin = uvsPool  + verticesOffset;
            uvsEnd   = uvsBegin + verticesBatch;
        }
    }

    /// ## --------------------------------------------------------

    /// ## This object is created and populated
    /// ## from "GraphicsMeshModel::requestMesh and resetMeshes"
    friend class GraphicsMeshModel;


    /// ## Where are we in the "GraphicsMeshModel::datapools"
    x_count     verticesOffset;
    x_count     indicesOffset;

    x_count indicesBatch;
    x_count verticesBatch;

    v_index    *indicesBegin{nullptr};
    v_index    *indicesEnd{nullptr};

    x_vector3  *positionsBegin{nullptr};
    x_vector3  *positionsEnd{nullptr};

    x_vector2  *uvsBegin{nullptr};
    x_vector2  *uvsEnd{nullptr};
    /// ## Add rest of pools here
    /// rgba, uvData, normals, tangents



    /// ## ------------------------------------------------------------------


};

}


#endif // MESHVIEW_H
