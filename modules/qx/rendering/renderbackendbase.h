#ifndef RENDERBACKENDBASE_H
#define RENDERBACKENDBASE_H

#include <core/metaobject.h>
#include <misc/meshmodel.h>



namespace Qx::prv
{

class GraphicsWindow;


class RenderBackendBase : public MetaObject
{
    QX_META_OBJECT( RenderBackendBase, MetaItemType::NA, MetaItemType::NA)


public:
    RenderBackendBase(GraphicsWindow *winItm);
    virtual BackendResult initBackend(const x_size &sz);
    virtual BackendResult beginFrame();
    virtual BackendResult endFrame();
    virtual BackendResult renderGraphicsView( prv::GraphicsView *grphxView );
    virtual BackendResult renderMeshModel(const MeshModel *mshModel);

protected:
    void setWindowSwapChain( void *swc);
    void *windowSwapChain();

protected:

    GraphicsWindow  *m_windowItem;
};

}

#endif // RENDERBACKENDBASE_H
