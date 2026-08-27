#ifndef SKIA_BASE_H
#define SKIA_BASE_H

#include "skia_helpers.h"

#include <rendering/canvasbase.h>

#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkPictureRecorder.h>
#include <skia/include/core/SkPicture.h>
#include <skia/include/gpu/ganesh/gl/GrGLDirectContext.h>  // For GrDirectContexts
#include <skia/include/gpu/ganesh/GrDirectContext.h>
#include <skia/include/core/SkFontMgr.h>
#include <skia/include/gpu/ganesh/GrDirectContext.h>
#include <skia/include/core/SkTypeface.h>

namespace Qx::prv
{


class SkiaBase : public CanvasBase
{
    friend class GraphicsScene;

public:
    SkiaBase( GraphicsWindow *winItm,
             filament::Scene *filamentScn);
    void snapshot( const std::string &flName );


protected:
    void drawSkiaShapes();

protected:
    void presentToSurface(SDL_Surface *sdlSurface,
                          const x_size &sz) override final;
    void presentToTexture(SDL_Texture *sdlTexture,
                          SDL_Renderer *sdlRenderer,
                          const x_size &sz) override final;



protected:
    void loadFontsDB();

protected:
    sk_sp<SkSurface>            m_skiaSurface;
    SkCanvas*                   m_skiaCanvas;
    sk_sp<GrDirectContext>      m_skiaContext;
    sk_sp<SkFontMgr>            m_skiaFontsManager;



};

}
#endif // SKIA_BASE_H
