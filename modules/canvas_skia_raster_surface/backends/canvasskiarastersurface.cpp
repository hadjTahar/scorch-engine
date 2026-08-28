#include "canvasskiarastersurface.h"



namespace Qx::Backend
{


CanvasSkiaRasterSurface::CanvasSkiaRasterSurface(prv::GraphicsWindow *winItm):
    CanvasSkiaRasterBase{ winItm }
{
    m_canvasTarget = prv::CanvasTarget::SDLSurface;
}



}
