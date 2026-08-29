#include "canvasskiarastertexture.h"



namespace Qx::Backend
{


CanvasSkiaRasterTexture::CanvasSkiaRasterTexture(prv::GraphicsWindow *winItm):
    CanvasSkiaRasterBase{ winItm }
{
    m_canvasTarget = prv::CanvasTarget::SDLTexture;
}

}
