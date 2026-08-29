#include "filamentbackend.h"

#include <core/graphicswindow.h>
#include <filament/SwapChain.h>
#include <misc/platfrom.h>


namespace Qx::Backend
{


FilamentBackend::FilamentBackend(prv::GraphicsWindow *winItm):
    prv::RenderBackendBase{ winItm },
    m_filamentSwapChain{ nullptr }
{
}

prv::BackendResult FilamentBackend::initBackend(const x_size &sz)
{
    if( !m_filamentEngine )
        m_filamentEngine = filament::Engine::create();
    dbg_assert( m_filamentEngine ) << "Invalid m_filamentEngine";

    if( !m_filamentRenderer )
        m_filamentRenderer  = m_filamentEngine->createRenderer();
    dbg_assert( m_filamentRenderer ) << "Invalid m_filamentRenderer";

    auto winSwapChain = windowSwapChain();
    if( winSwapChain )
        m_filamentSwapChain = static_cast<filament::SwapChain*>( winSwapChain );
    else{
        auto nativeWin = prv::Platfrom::nativeWindowHandle( m_windowItem->sdlWindow() );
        m_filamentSwapChain = m_filamentEngine->createSwapChain( nativeWin );
        dbg_assert( m_filamentSwapChain ) << "Invalid m_filamentSwapChain";
        setWindowSwapChain( m_filamentSwapChain );
    }

    return prv::BackendResult::SUCCESS;
}

Qx::prv::BackendResult FilamentBackend::renderMeshModel(const MeshModel *mshModel)
{
    return prv::BackendResult::SUCCESS;
}

}
