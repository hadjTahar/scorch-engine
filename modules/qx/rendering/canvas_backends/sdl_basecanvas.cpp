#include "sdlbasecanvas.h"

namespace Qx::prv
{


SDLBaseCanvas::SDLBaseCanvas(SDL_Window *sdlWin, SDL_Renderer *sdlRndr):
    CanvasBase{ sdlWin, sdlRndr }
{
}


void SDLBaseCanvas::drawRect(const RectShape &rcShape)
{
    if constexpr( QX_DEF_CANVAS_IMMEDIATE_MODE )
        immediateDrawRect(rcShape);
    else
        m_shapesitems.push_back( rcShape );
}

void SDLBaseCanvas::drawRRect(const RoundedRectShape &rrcShape)
{
    if constexpr( QX_DEF_CANVAS_IMMEDIATE_MODE )
        immediateDrawRRect(rrcShape);
    else
        m_shapesitems.push_back( rrcShape );
}

void SDLBaseCanvas::drawArc(const ArcShape &arcShape)
{
    if constexpr( QX_DEF_CANVAS_IMMEDIATE_MODE )
        immediateDrawArc(arcShape);
    else
        m_shapesitems.push_back( arcShape );
}


void SDLBaseCanvas::present()
{
    for ( const auto& shp : m_shapesitems) {
        std::visit(overloaded{
                              [](const std::monostate &) {},
                              [this](const RectShape &shp)   { immediateDrawRect(shp); },
                              [this](const RoundedRectShape &shp)   { immediateDrawRRect(shp); },
                              [this](const ArcShape &shp)   { immediateDrawArc(shp); },
                              },
                   shp);
    }
}

}
