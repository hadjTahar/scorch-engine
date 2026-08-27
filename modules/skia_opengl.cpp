#include "skia_opengl.h"

#include <filament/RenderTarget.h>
#include <skia/include/gpu/ganesh/SkSurfaceGanesh.h>




namespace Qx::prv
{


SkiaOPENGL::SkiaOPENGL(SDL_Window *sdlWin, filament::Scene *filScn):
    Qx::prv::SkiaBase{ sdlWin, filScn }
{

}

BackendResult SkiaOPENGL::initBackend(const x_size &sz)
{
    SDL_GLContext gl = SDL_GL_CreateContext( m_sdlWindow );
    dbg_assert( gl ) << "Invalid SDL_GLContext, SDL window has no OpenGL, "
                      "make sure it was created with SDL_WINDOW_OPENGL option, "
                      "check QX_OPT_SDL_WINDOW_OPTIONS";
    SDL_GL_MakeCurrent(m_sdlWindow , gl);

    m_skiaInterface = GrGLMakeNativeInterface();
    dbg_assert( m_skiaInterface.get() ) <<
        "Invalid Opengl GrGLInterface interface, make sure skia is built with skia_use_gl=true";
    m_skiaContext = GrDirectContexts::MakeGL(m_skiaInterface);
    dbg_assert( m_skiaContext.get() ) <<
        "Invalid Opengl GrDirectContext, make sure skia is built with skia_use_gl=true";

    return BackendResult::SUCCESS;
}

BackendResult SkiaOPENGL::renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp)
{
    if( !m_skiaContext )
        return BackendResult::ERROR;

    const auto ww = m_skiaSurface? m_skiaSurface->width() : 0;
    const auto hh = m_skiaSurface? m_skiaSurface->height() : 0;
    const auto sameSize = (ww == sz.width) && (hh == sz.height);
    if( !sameSize )
    {
        const auto pxPair = helpers::skiaSdlPXFormats(pxFormat,pxAlphaTp);
        SkImageInfo info  = SkImageInfo::Make(sz.width,
                                             sz.height,
                                             pxPair.colorType,
                                             pxPair.alphaType);


        m_skiaSurface = SkSurfaces::RenderTarget(
            m_skiaContext.get(),
            skgpu::Budgeted::kYes,
            info
            );
        dbg_assert( m_skiaSurface.get() ) <<
            "Invalid SkSurface";
        m_skiaCanvas = m_skiaSurface->getCanvas();
        dbg_assert( m_skiaSurface.get() ) << "Invalid SkCanvas";
    }


    drawSkiaShapes();

    /// For Skia OpenGL you need to
    if( m_skiaContext ){
       m_skiaContext->flushAndSubmit();
    }
    return BackendResult::SUCCESS;
}


}
