#include "canvasskiaopenglsurface.h"



namespace Qx::prv
{


CanvasSkiaOpenGLSurface::CanvasSkiaOpenGLSurface(GraphicsWindow *winItm):
    Qx::prv::CanvasSkiaOpenGLBase{ winItm }
{
    m_canvasTarget = CanvasTarget::SDLSurface;
}



}
