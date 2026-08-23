#ifndef CANVASBASE_H
#define CANVASBASE_H

#include "canvasshape.h"

#include <core/metaobject.h>
#include <misc/font.h>
#include <misc/pixelformats.h>

#include <SDL3/SDL_render.h>
#include <filament/Engine.h>
#include <filament/Scene.h>

namespace Qx::prv
{

class CanvasBase : public MetaObject
{
    QX_META_OBJECT( CanvasBase, MetaItemType::NA, MetaItemType::NA)

public:
    CanvasBase(SDL_Window *sdlWin, filament::Scene *filScn );
    virtual ~CanvasBase();

    virtual BackendResult initBackend(const x_size &sz)
    {
        dbg_print() << "initBackend is not implemented, defaulting to "
                       "CanvasBase::initBackend";

        return BackendResult::SUCCESS;
    }

    virtual BackendResult renderShapes(const x_size &,
                                       PixelFormat,
                                       PixelAlphaType )
    {
        dbg_print() << "renderShapes is not implemented, defaulting to "
                       "CanvasBase::renderShapes";
        return BackendResult::SUCCESS;
    }

    virtual void presentToSurface(SDL_Surface *,
                                  const x_size &)
    {
        dbg_print() << "presentToSurface is not implemented, defaulting to "
                       "CanvasBase::presentToSurface";
    }

    virtual void presentToTexture( SDL_Texture *,
                                  SDL_Renderer *,
                                  const x_size &)
    {
        dbg_print() << "presentToTexture is not implemented, defaulting to "
                       "CanvasBase::presentToTexture";
    }


    void render(const x_size &sz);

    void drawRect( const x_rect &rc,
                  const CanvasPen &pen,
                  const CanvasBrush &brush );
    void drawRRect(const x_rrect &rrc,
                   const CanvasPen &pen,
                   const CanvasBrush &brush);
    void drawCircle(x_real xx, x_real yy, x_real rad,
                    const CanvasPen &pen,
                    const CanvasBrush &brush);
    void drawCanvasPath(const CanvasPath &path,
                        const CanvasPen &pen,
                        const CanvasBrush &brush);
    void drawSimpleText(const x_string &text,
                        const Font &fnt,
                        const x_rect &rc,
                        const CanvasPen &pen );

    void drawSimpleText(const x_string   &text,
                        const TextFormat &format,
                        const CanvasPen  &pen);

    void drawImage( const x_string &source,
                   const x_size &size);



    bool antialias() const;
    void setAntialias(bool newAntialias);

    filament::Engine   *filamentEngine() const;
    filament::Scene    *filamentScene() const;

    x_matrix4x4 matrix() const;
    void setMatrix(const x_matrix4x4 &newMatrix);



private:
    PixelAlphaType pixelAlphaType(SDL_PixelFormat sdlPxFormat,
                                  const SDL_PixelFormatDetails *sdlPxDetails);
    SDL_Surface *updateSDLSurface();
    SDL_Texture *updateSDLTexture(const x_size &sz);

protected:
    std::vector<CanvasShape> m_shapes;
    SDL_Window           *m_sdlWindow;
    filament::Engine     *m_filamentEngine;
    filament::Scene      *m_filamentScene;
    x_matrix4x4           m_matrix;
    bool                  m_antialias;


    /// ## Targets
    SDL_Renderer *m_sdlRenderer;
    SDL_Texture  *m_sdlTexture;

};

}

#endif // CANVASBASE_H
