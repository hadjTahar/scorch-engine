#ifndef RENDERBACKENDSAMPLE_H
#define RENDERBACKENDSAMPLE_H

#include <rendering/renderbackendbase.h>


namespace Qx::Backend
{

class RenderBackendSample : public prv::RenderBackendBase
{


    template <typename BackendType>
    friend class Qx::prv::GraphicsScene3D;

public:

    RenderBackendSample(prv::GraphicsWindow *winItm);

protected:
    virtual prv::BackendResult initBackend(const x_size &sz);
    virtual prv::BackendResult beginFrame();
    virtual prv::BackendResult endFrame();
    virtual prv::BackendResult renderGraphicsView( prv::GraphicsView *grphxView,
                                             x_count viewIndex );
    virtual prv::BackendResult renderMeshModel( GraphicsMeshModel *mshModel);

    static void printTrackers();
    virtual std::unique_ptr<GraphicsMeshModel> createMeshModel();
};

}


#endif // RENDERBACKENDSAMPLE_H
