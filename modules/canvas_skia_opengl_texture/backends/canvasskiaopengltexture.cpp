#include "canvasskiaopengltexture.h"



namespace Qx::prv
{


CanvasSkiaOpenGLTexture::CanvasSkiaOpenGLTexture(GraphicsWindow *winItm):
    Qx::prv::CanvasSkiaOpenGLBase{ winItm }
{
    m_canvasTarget = CanvasTarget::SDLTexture;
}



}
