#ifndef SDL_RASTER_H
#define SDL_RASTER_H




#include "sdlbasecanvas.h"

namespace Qx::prv
{


class SDLRaster : public SDLBaseCanvas
{
public:
    SDLRaster(SDL_Window *sdlWin, SDL_Renderer *sdlRndr):SDLBaseCanvas{sdlWin, sdlRndr}{}
    CanvasResult init() override final{return CanvasResult::SUCCESS;}
    CanvasResult startCanvas( x_real, x_real) override final{return CanvasResult::SUCCESS;}
    CanvasResult endCanvas() override final{present();return CanvasResult::SUCCESS;}

protected:

    void immediateDrawRect( const RectShape &rcShape ) override final{}
    void immediateDrawRRect( const RoundedRectShape &rrcShape ) override final{}
    void immediateDrawArc( const ArcShape &arcShape ) override final{}
};


}

namespace Qx{using Canvas = Qx::prv::SDLRaster;}

#endif // SDL_RASTER_H
