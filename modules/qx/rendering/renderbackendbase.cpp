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

BackendResult RenderBackendBase::renderMeshModel(const MeshModel *mshModel)
{
    dbg_print() << "renderMeshModel is not implemented, defaulting to "
                   "BackendResult::renderMeshModel";
    return BackendResult::SUCCESS;
}

void RenderBackendBase::setWindowSwapChain(void *swc)
{
    if( !m_windowItem )
        return;
    if( m_windowItem->m_renderBackendSwapChain ){
        dbg_assert( m_windowItem->m_renderBackendSwapChain == swc ) <<
            "Swap chains for same window supposed to be the same";
        return;
    }
    m_windowItem->m_renderBackendSwapChain = swc;
}

void *RenderBackendBase::windowSwapChain()
{
    if( !m_windowItem )
        return nullptr;
    return m_windowItem->m_renderBackendSwapChain;
}



}
