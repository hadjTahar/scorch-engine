#ifndef FILAMENTMESHMODEL_H
#define FILAMENTMESHMODEL_H

#include "graphicsmeshmodel.h"

#include <glm/gtc/type_ptr.hpp>

#include <filament/Engine.h>
#include <utils/EntityManager.h>
#include <filament/Viewport.h>
#include <filament/View.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

#include <filament/IndexBuffer.h>
#include <filament/VertexBuffer.h>
#include <filament/RenderableManager.h>

#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/Camera.h>
#include <filament/Skybox.h>
#include <filament/Engine.h>
#include <filament/SwapChain.h>

namespace Qx {

namespace Backend
{
class FilamentBackend;
}


class FilamentMeshModel : public GraphicsMeshModel
{

    QX_META_OBJECT( "FilamentMeshModel",
                   prv::MetaItemType::NA,
                   prv::MetaItemType::NA )

    friend class Backend::FilamentBackend;

public:
    FilamentMeshModel();
    ~FilamentMeshModel();


protected:
    void clearBackendBuffers() override;

protected:


    void renderModel(filament::Engine *eng, filament::Scene  *scn);
    void updateVertexBuffer();
    void updateIndexBuffer();
    void updateMaterial();
    void updateEntity();



    /// ## Vertex buffer
    /// ## ------------------
    void buildVertexBuffers();
    void setVertexBuffers();
    void resetVertexBuffers();

    /// ## Index buffer
    /// ## ------------------
    void buildIndexBuffer();
    void setIndexBuffer();
    void resetIndexBuffer();

    /// ## Meterial buffer
    /// ## ------------------
    void buildMaterial();
    void resetMaterial();


    /// ## Entity
    /// ## ------------------
    void buildEntity();
    void resetEntity();
    void renderEntity();


    static auto convertMatrix(const x_matrix4x4& sourceGlmMatrix) {
        filament::math::mat4f targetMatrix;
        // Grabs raw float pointer, forcing a safe 64-byte block copy
        // without invoking Filament's multi-argument vector constructors
        const float* rawData = x_vector::value_ptr(sourceGlmMatrix);
        std::copy(rawData, rawData + 16, &targetMatrix[0].x);
        return targetMatrix;
    }

protected:

    filament::Engine *m_filamentEngine{nullptr};
    filament::Scene  *m_filamentScene{nullptr};


    /// ## Model data
    utils::Entity                m_filamentEntity;
    filament::Material          *m_filamentMaterial{nullptr};
    filament::MaterialInstance  *m_filamentMaterialInstance{nullptr};
    filament::VertexBuffer      *m_filamentVertexBuffer{nullptr};
    filament::IndexBuffer       *m_filamentIndexBuffer{nullptr};

};


}

#endif // FILAMENTMESHMODEL_H
