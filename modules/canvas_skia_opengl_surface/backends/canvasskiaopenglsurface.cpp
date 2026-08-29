#include "canvasskiaopenglsurface.h"



namespace Qx::Backend
{


CanvasSkiaOpenGLSurface::CanvasSkiaOpenGLSurface( prv::GraphicsWindow *winItm):
    CanvasSkiaOpenGLBase{ winItm }
{
    m_canvasTarget = prv::CanvasTarget::SDLSurface;
}



}
