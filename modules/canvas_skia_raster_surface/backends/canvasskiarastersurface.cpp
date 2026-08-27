#include "canvasskiarastersurface.h"



namespace Qx::prv
{


CanvasSkiaRasterSurface::CanvasSkiaRasterSurface(GraphicsWindow *winItm):
    Qx::prv::CanvasSkiaRasterBase{ winItm }
{
    m_canvasTarget = CanvasTarget::SDLSurface;
}



}
