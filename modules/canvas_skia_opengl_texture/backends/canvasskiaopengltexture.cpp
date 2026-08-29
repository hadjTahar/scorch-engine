#include "canvasskiaopengltexture.h"



namespace Qx::Backend
{


CanvasSkiaOpenGLTexture::CanvasSkiaOpenGLTexture(prv::GraphicsWindow *winItm):
    CanvasSkiaOpenGLBase{ winItm }
{
    m_canvasTarget = prv::CanvasTarget::SDLTexture;
}



}
