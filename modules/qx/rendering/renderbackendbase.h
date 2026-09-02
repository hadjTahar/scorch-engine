#ifndef RENDERBACKENDBASE_H
#define RENDERBACKENDBASE_H

#include "graphicsmeshmodel.h"
#include <core/metaobject.h>



namespace Qx::prv
{

class GraphicsWindow;
class GraphicsView;


class RenderBackendBase : public MetaObject
{
    QX_META_OBJECT( RenderBackendBase, MetaItemType::NA, MetaItemType::NA)


protected:
    RenderBackendBase(GraphicsWindow *winItm);
    virtual BackendResult initBackend(const x_size &sz);
    virtual BackendResult beginFrame();
    virtual BackendResult endFrame();
    virtual BackendResult renderGraphicsView( GraphicsView *grphxView,
                                             x_count viewIndex );
    virtual BackendResult renderMeshModel( GraphicsMeshModel *mshModel);

    static void printTrackers();
    virtual std::unique_ptr<GraphicsMeshModel> createMeshModel();

protected:
    void setWindowSwapChain( void *swc);
    void *windowSwapChain();

protected:

    GraphicsWindow  *m_windowItem;
};

}

#endif // RENDERBACKENDBASE_H
