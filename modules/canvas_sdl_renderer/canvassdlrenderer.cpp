#include "canvassdlrenderer.h"


namespace Qx::prv
{


CanvasSDLRenderer::CanvasSDLRenderer(GraphicsWindow *winItm):
    CanvasBase{winItm}
{

}

BackendResult CanvasSDLRenderer::initBackend(const x_size &sz)
{
    dbg_print() << "CanvasSDLRenderer::initBackend";
    return BackendResult::SUCCESS;
}

BackendResult CanvasSDLRenderer::renderShapes(const x_size &, PixelFormat, PixelAlphaType)
{
    dbg_print() << "CanvasSDLRenderer::renderShapes";

    return BackendResult::SUCCESS;
}

void CanvasSDLRenderer::presentToSurface(SDL_Surface *, const x_size &)
{
    dbg_print() << "CanvasSDLRenderer::presentToSurface";

}

void CanvasSDLRenderer::presentToTexture(SDL_Texture *, SDL_Renderer *, const x_size &)
{
    dbg_print() << "CanvasSDLRenderer::presentToTexture";

}

}
