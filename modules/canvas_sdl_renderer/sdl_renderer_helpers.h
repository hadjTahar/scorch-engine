#ifndef SDL_RENDERER_HELPERS_H
#define SDL_RENDERER_HELPERS_H

#include <misc/vecs.h>
#include <SDL3/SDL_render.h>
#include <rendering/canvasshape.h>


namespace Qx::backend::renderer {



static inline void drawRect( SDL_Renderer *sdlRenderer, const prv::CanvasShape &shp)
{
    dbg_print() << "drawRect not implemented yet";

    const x_rect rc{shp.data[0], shp.data[1], shp.data[2], shp.data[3]};
    const SDL_FRect  sdlRC{ rc.x, rc.y, rc.width, rc.height };

    // const auto rcClr = shp.pen.color();
    SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255); // Red color
    SDL_RenderRect(sdlRenderer, &sdlRC);
}

static inline void drawRRect( SDL_Renderer *sdlRenderer, const prv::CanvasShape &shp)
{
    dbg_print() << "drawRRect not implemented yet";
}

static inline void drawCircle( SDL_Renderer *sdlRenderer, const prv::CanvasShape &shp)
{
    dbg_print() << "drawCircle not implemented yet";
}

static inline void drawPath( SDL_Renderer *sdlRenderer, const prv::CanvasShape &shp)
{
    dbg_print() << "drawPath not implemented yet";
}

static inline void drawText( SDL_Renderer *sdlRenderer, const prv::CanvasShape &shp)
{
    dbg_print() << "drawText not implemented yet";
}

static inline void drawImage( SDL_Renderer *sdlRenderer, const prv::CanvasShape &shp)
{
    dbg_print() << "drawImage not implemented yet";
}



}

#endif // SDL_RENDERER_HELPERS_H
