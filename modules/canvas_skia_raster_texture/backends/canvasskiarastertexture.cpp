#include "canvasskiarastertexture.h"



namespace Qx::prv
{


CanvasSkiaRasterTexture::CanvasSkiaRasterTexture(GraphicsWindow *winItm):
    Qx::prv::CanvasSkiaRasterBase{ winItm }
{
    m_canvasTarget = CanvasTarget::SDLTexture;
}

}
