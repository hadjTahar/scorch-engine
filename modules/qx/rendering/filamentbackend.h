#ifndef FILAMENTBACKEND_H
#define FILAMENTBACKEND_H

#include "renderbackendbase.h"
#include <filament/Engine.h>
#include <properties/cameraproperties.h>



namespace Qx::Backend
{

class FilamentBackend : public prv::RenderBackendBase
{
public:
    FilamentBackend( prv::GraphicsWindow *winItm);
    ~FilamentBackend();

    /// ## Called when scene destroy
    void destroyScene();

    /// ## Called when window destroy
    void destroySwapChain();

    /// ## Called when app destroy
    static void destroyEngine();



    prv::BackendResult beginFrame() override;
    prv::BackendResult endFrame() override;
    prv::BackendResult initBackend(const x_size &sz) override;
    prv::BackendResult renderGraphicsView( prv::GraphicsView *grphxView,
                                          x_count viewIndex ) override;
    prv::BackendResult renderMeshModel(const MeshModel *mshModel) override;


protected:
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
