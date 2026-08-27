#ifndef CANVASSDLRENDERER_H
#define CANVASSDLRENDERER_H

#include <rendering/canvasbase.h>


namespace Qx::prv
{


class CanvasSDLRenderer : public CanvasBase
{
public:
    CanvasSDLRenderer(GraphicsWindow *winItm);


    BackendResult initBackend(const x_size &sz) override;
    BackendResult renderShapes(const x_size &,
                               PixelFormat,
                               PixelAlphaType ) override;

    void presentToSurface(SDL_Surface *,
                          const x_size &) override;

    void presentToTexture( SDL_Texture *,
                          SDL_Renderer *,
                          const x_size &) override;
};

}

#endif // CANVASSDLRENDERER_H
