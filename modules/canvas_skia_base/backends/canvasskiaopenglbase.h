#ifndef CANVASSKIAOPENGLBASE_H
#define CANVASSKIAOPENGLBASE_H



#include <skia/include/gpu/ganesh/gl/GrGLInterface.h>
#include <skia/include/gpu/ganesh/SkSurfaceGanesh.h>





#include "canvasskiabase.h"

namespace Qx::prv
{


class CanvasSkiaOpenGLBase : public CanvasSkiaBase
{
public:
    CanvasSkiaOpenGLBase(GraphicsWindow *winItm):
        Qx::prv::CanvasSkiaBase{ winItm },
        m_sdlGLContext{ nullptr }
    {
    }
    ~CanvasSkiaOpenGLBase()
    {
        if( m_sdlGLContext ){
            m_skiaSurface.reset();
            m_skiaContext.reset();
            m_skiaInterface.reset();
            SDL_GL_DestroyContext( m_sdlGLContext );
            m_sdlGLContext = nullptr;
        }
    }

    virtual BackendResult initBackend(const x_size &sz) override
    {
        dbg_assert( !m_sdlGLContext ) << "SDL GL Context already exists";
        auto sdlWindow = m_windowItem->sdlWindow();
        m_sdlGLContext = SDL_GL_CreateContext( sdlWindow );
        dbg_assert( m_sdlGLContext ) << "Invalid SDL_GLContext, SDL window has no OpenGL, "
                          "make sure it was created with SDL_WINDOW_OPENGL option, "
                          "check QX_OPT_SDL_WINDOW_OPTIONS";
        SDL_GL_MakeCurrent(sdlWindow , m_sdlGLContext);

        m_skiaInterface = GrGLMakeNativeInterface();
        dbg_assert( m_skiaInterface.get() ) <<
            "Invalid Opengl GrGLInterface interface, make sure skia is built with skia_use_gl=true";
        m_skiaContext = GrDirectContexts::MakeGL(m_skiaInterface);
        dbg_assert( m_skiaContext.get() ) <<
            "Invalid Opengl GrDirectContext, make sure skia is built with skia_use_gl=true";

        return BackendResult::SUCCESS;
    }


    virtual BackendResult renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp) override
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
private:
    SDL_GLContext m_sdlGLContext;
    sk_sp<const GrGLInterface>  m_skiaInterface;
};

}


#endif // CANVASSKIAOPENGLBASE_H
