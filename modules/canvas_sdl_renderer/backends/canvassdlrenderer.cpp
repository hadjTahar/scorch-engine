#include "canvassdlrenderer.h"
#include "../sdl_renderer_helpers.h"

#include <core/graphicswindow.h>


namespace Qx::Backend
{


CanvasSDLRenderer::CanvasSDLRenderer(prv::GraphicsWindow *winItm):
    prv::CanvasBase{winItm}
{
    m_canvasTarget = prv::CanvasTarget::SDLRenderer;

}

prv::BackendResult CanvasSDLRenderer::initBackend(const x_size &sz)
{
    const auto sdlRenderer = m_windowItem->sdlRenderer();
    dbg_assert( sdlRenderer ) << "Invalid SDL renderer...";
    return prv::BackendResult::SUCCESS;
}

prv::BackendResult CanvasSDLRenderer::renderShapes(const x_size &,
                                              prv::PixelFormat,
                                              prv::PixelAlphaType)
{
    auto sdlRenderer = m_windowItem->sdlRenderer();
    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
    // SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlRenderer);

    dbg_assert( sdlRenderer ) << "Invalid SDL renderer...";
    for ( const auto &shp : m_shapes) {

        const auto shpTp = shp.type;

        switch (shpTp) {
        case prv::CanvasShapeType::Rect:{
            Qx::Backend::drawRect( sdlRenderer, shp );
            break;
        }
        case prv::CanvasShapeType::RRect:{
            Qx::Backend::drawRRect( sdlRenderer, shp );
            break;
        }
        case prv::CanvasShapeType::Circle:{
            Qx::Backend::drawCircle( sdlRenderer, shp );
            break;
        }
        case prv::CanvasShapeType::Path:{
            Qx::Backend::drawPath( sdlRenderer, shp );
            break;
        }
        case prv::CanvasShapeType::Text:{
            Qx::Backend::drawText( sdlRenderer, shp );
            break;
        }
        case prv::CanvasShapeType::Image:{
            Qx::Backend::drawImage( sdlRenderer, shp );
            break;
        }

        default:
            dbg_assert( false )<< "Shape type: "
                              << static_cast<int>( shpTp)
                              << "not supported yet";
            break;
        }

    }

    SDL_RenderPresent(sdlRenderer);
    return prv::BackendResult::SUCCESS;
}

void CanvasSDLRenderer::presentToSurface(SDL_Surface *,
                                         const x_size &)
{

}

void CanvasSDLRenderer::presentToTexture(SDL_Texture *,
                                         SDL_Renderer *,
                                         const x_size &)
{

}

}
