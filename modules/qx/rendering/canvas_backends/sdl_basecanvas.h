#ifndef SDL_BASECANVAS_H
#define SDL_BASECANVAS_H

#include <canvas/canvasbase.h>



namespace Qx::prv
{


class SDLBaseCanvas : public CanvasBase
{
public:
    SDLBaseCanvas(SDL_Window *sdlWin, SDL_Renderer *sdlRndr );

    void drawRect( const RectShape &rcShape ) override final;
    void drawRRect( const RoundedRectShape &rrcShape ) override final;
    void drawArc( const ArcShape &arcShape )  override final;

protected:
    void present();

    virtual void immediateDrawRect( const RectShape &rcShape ) = 0;
    virtual void immediateDrawRRect( const RoundedRectShape &rrcShape ) = 0;
    virtual void immediateDrawArc( const ArcShape &arcShape ) = 0;

protected:
    std::vector<ShapeVariant> m_shapesitems;

};

}
#endif // SDL_BASECANVAS_H
