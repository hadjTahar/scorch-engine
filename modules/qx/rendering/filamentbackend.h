#ifndef FILAMENTBACKEND_H
#define FILAMENTBACKEND_H

#include "renderbackendbase.h"
#include <filament/Engine.h>



namespace Qx::Backend
{

class FilamentBackend : public prv::RenderBackendBase
{
public:
    FilamentBackend( prv::GraphicsWindow *winItm);


    virtual prv::BackendResult initBackend(const x_size &sz);
    virtual prv::BackendResult renderMeshModel(const MeshModel *mshModel);

protected:

    inline static filament::Engine   *m_filamentEngine{nullptr};
    inline static filament::Renderer *m_filamentRenderer{nullptr};


    filament::SwapChain       *m_filamentSwapChain;

    /// ## Scene, view, camera


};

}
#endif // FILAMENTBACKEND_H
