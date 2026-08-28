#ifndef CANVASSDLRENDERER_H
#define CANVASSDLRENDERER_H

#include <rendering/canvasbase.h>


namespace Qx::Backend
{


class CanvasSDLRenderer : public prv::CanvasBase
{
public:
    CanvasSDLRenderer(prv::GraphicsWindow *winItm);


    prv::BackendResult initBackend(const x_size &sz) override;
    prv::BackendResult renderShapes(const x_size &,
                               prv::PixelFormat,
                               prv::PixelAlphaType ) override;

    void presentToSurface(SDL_Surface *,
                          const x_size &) override;

    void presentToTexture( SDL_Texture *,
                          SDL_Renderer *,
                          const x_size &) override;
};

}

#endif // CANVASSDLRENDERER_H
