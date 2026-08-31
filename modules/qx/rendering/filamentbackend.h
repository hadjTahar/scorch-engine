#ifndef FILAMENTBACKEND_H
#define FILAMENTBACKEND_H

#include "renderbackendbase.h"
#include <properties/cameraproperties.h>


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




namespace Qx::Backend
{

class FilamentBackend : public prv::RenderBackendBase
{
public:
    FilamentBackend( prv::GraphicsWindow *winItm);
    ~FilamentBackend();

    /// ## What a Render Backend needs
    /// ##

    prv::BackendResult beginFrame() override;
    prv::BackendResult endFrame() override;
    prv::BackendResult initBackend(const x_size &sz) override;
    prv::BackendResult renderGraphicsView( prv::GraphicsView *grphxView,
                                          x_count viewIndex ) override;
    prv::BackendResult renderMeshModel(const GraphicsMeshModel *mshModel) override;

    std::unique_ptr<GraphicsMeshModel> createMeshModel() override;

    filament::Scene *filamentScene() const;
    static filament::Engine *filamentEngine();
    static filament::Renderer *filamentRenderer();
    static void printTrackers();

protected:
    /// ## Called when scene destroy
    void destroyScene();
    /// ## Called when window destroy
    void destroySwapChain();
    /// ## Called when app destroy
    static void destroyEngine();


    prv::BackendResult addView( prv::GraphicsView *vw );
    void applyCamera( filament::Camera* flmntCam,
                     const prv::CameraProperties &camProperties );



protected:

    inline static bool                m_created{false};
    inline static filament::Engine   *m_filamentEngine{nullptr};
    inline static filament::Renderer *m_filamentRenderer{nullptr};


    filament::SwapChain *m_filamentSwapChain;
    filament::Scene     *m_filamentScene;

    std::vector<filament::View*>    m_filamentViews;
    std::vector<filament::Camera*>  m_filamentCameras;


};

}
#endif // FILAMENTBACKEND_H
