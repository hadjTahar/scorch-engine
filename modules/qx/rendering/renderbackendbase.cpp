#include "renderbackendbase.h"
#include <core/graphicswindow.h>

namespace Qx::prv
{

RenderBackendBase::RenderBackendBase(GraphicsWindow *winItm):
    m_windowItem{ winItm }
{

}

BackendResult RenderBackendBase::initBackend(const x_size &sz)
{
    dbg_print() << "initBackend is not implemented, defaulting to "
                   "BackendResult::initBackend";
    return BackendResult::SUCCESS;
}

BackendResult RenderBackendBase::beginFrame()
{
    dbg_print() << "beginFrame is not implemented, defaulting to "
                   "BackendResult::beginFrame";
    return BackendResult::SUCCESS;
}

BackendResult RenderBackendBase::endFrame()
{
    dbg_print() << "beginFrame is not implemented, defaulting to "
                   "BackendResult::beginFrame";
    return BackendResult::SUCCESS;
}

BackendResult RenderBackendBase::renderGraphicsView(prv::GraphicsView *grphxView,
                                                    x_count viewIndex)
{
    dbg_print() << "renderGraphicsView is not implemented, defaulting to "
                   "BackendResult::renderGraphicsView";
    return BackendResult::SUCCESS;
}

BackendResult RenderBackendBase::renderMeshModel(const GraphicsMeshModel *mshModel)
{
    dbg_print() << "renderMeshModel is not implemented, defaulting to "
                   "BackendResult::renderMeshModel";
    return BackendResult::SUCCESS;
}

void RenderBackendBase::printTrackers()
{
    dbg_print_st() << "printTrackers is not implemented, defaulting to "
                   "BackendResult::printTrackers";
}

std::unique_ptr<GraphicsMeshModel> RenderBackendBase::createMeshModel()
{
    dbg_print_st() << "createMeshModel is not implemented, defaulting to "
                      "BackendResult::createMeshModel";

    auto ret = make_unique_meta<GraphicsMeshModel>();
    return std::move( ret );
}


// BackendResult RenderBackendBase::addView(GraphicsView *vw)
// {
//     dbg_print() << "addView is not implemented, defaulting to "
//                    "BackendResult::addView";
//     return BackendResult::SUCCESS;
// }

void RenderBackendBase::setWindowSwapChain(void *swc)
{
    if( !m_windowItem )
        return;
    dbg_assert( !m_windowItem->m_filamentBackendSwapChain) <<
        "Window already has a swap chain, "
        "use ::windowSwapChain to get it";
    return;
    m_windowItem->m_filamentBackendSwapChain = swc;
}

void *RenderBackendBase::windowSwapChain()
{
    if( !m_windowItem )
        return nullptr;
    return m_windowItem->m_filamentBackendSwapChain;
}



}
