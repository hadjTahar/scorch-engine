#include "canvassdlrenderer.h"
#include "../sdl_renderer_helpers.h"

#include <core/graphicswindow.h>


namespace Qx::prv
{


CanvasSDLRenderer::CanvasSDLRenderer(GraphicsWindow *winItm):
    CanvasBase{winItm}
{

}

BackendResult CanvasSDLRenderer::initBackend(const x_size &sz)
{
    const auto sdlRenderer = m_windowItem->sdlRenderer();
    dbg_assert( sdlRenderer ) << "Invalid SDL renderer...";
    return BackendResult::SUCCESS;
}

BackendResult CanvasSDLRenderer::renderShapes(const x_size &, PixelFormat, PixelAlphaType)
{
    auto sdlRenderer = m_windowItem->sdlRenderer();
    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
    // SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 0);
    SDL_RenderClear(sdlRenderer);

    dbg_assert( sdlRenderer ) << "Invalid SDL renderer...";
    for ( const auto &shp : m_shapes) {

        const auto shpTp = shp.type;

        switch (shpTp) {
        case CanvasShapeType::Rect:{
            Qx::prv::helpers::drawRect( sdlRenderer, shp );
            break;
        }
        case CanvasShapeType::RRect:{
            Qx::prv::helpers::drawRRect( sdlRenderer, shp );
            break;
        }
        case CanvasShapeType::Circle:{
            Qx::prv::helpers::drawCircle( sdlRenderer, shp );
            break;
        }
        case CanvasShapeType::Path:{
            Qx::prv::helpers::drawPath( sdlRenderer, shp );
            break;
        }
        case CanvasShapeType::Text:{
            Qx::prv::helpers::drawText( sdlRenderer, shp );
            break;
        }
        case CanvasShapeType::Image:{
            Qx::prv::helpers::drawImage( sdlRenderer, shp );
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
    return BackendResult::SUCCESS;
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
