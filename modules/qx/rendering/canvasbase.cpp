#include "canvasbase.h"

#include <core/graphicswindow.h>


namespace Qx::prv
{

CanvasBase::CanvasBase(GraphicsWindow *winItm,
                       filament::Scene *filamentScn):
    m_windowItem{ winItm },
    m_filamentScene{filamentScn},
    m_sdlTexture{ nullptr }
{
}

CanvasBase::~CanvasBase()
{
    if( m_sdlTexture )
        SDL_DestroyTexture( m_sdlTexture );


}

void CanvasBase::render(const x_size &sz)
{
    const CanvasTarget targetTp = QX_DEF_CANVAS_TARGET;

    if constexpr (targetTp == CanvasTarget::SDLSurface ){
        auto sdlSurface = updateSDLSurface();
        const auto sdlPxFormat   = sdlSurface->format;
        const auto *sdlPxDetails = SDL_GetPixelFormatDetails( sdlPxFormat );

        const auto pxFormat = static_cast<PixelFormat>( sdlPxFormat);
        const auto alphTp   = pixelAlphaType( sdlPxFormat, sdlPxDetails );
        renderShapes(sz, pxFormat, alphTp );
        presentToSurface( sdlSurface , sz );
    }

    /// XX Don't call "presentToTexture( updateSDLTexture( sz ), sdlRenderer);"
    else if constexpr (targetTp == CanvasTarget::SDLTexture ){
        auto sdlText = updateSDLTexture( sz );
        const auto sdlPxFormat   = sdlText->format;
        const auto *sdlPxDetails = SDL_GetPixelFormatDetails( sdlPxFormat );

        const auto pxFormat = static_cast<PixelFormat>( sdlPxFormat);
        const auto alphTp   = pixelAlphaType( sdlPxFormat, sdlPxDetails );
        renderShapes(sz, pxFormat, alphTp );
        // presentToTexture( sdlText, m_windowItem->sdlRenderer() );
        presentToTexture( sdlText, m_windowItem->sdlRenderer(), sz);
    }


    else if constexpr (targetTp == CanvasTarget::GoolgeFilament )
        dbg_assert( false ) << "CanvasTarget::GoolgeFilament is Not supported yet";
    else
        dbg_assert( false ) << "No supported canvas target selected, check QX_OPT_CANVAS_TARGET";
    m_shapes.clear();
}


void CanvasBase::drawRect(const x_rect &rc,
                          const CanvasPen &pen,
                          const CanvasBrush &brush)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::Rect;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    /// ## Max values is 10
    ret.data      = {rc.x,rc.y,rc.width,rc.height};
    ret.pen       = pen;
    ret.brush     = brush;

    m_shapes.push_back( ret );
}

void CanvasBase::drawRRect(const x_rrect &rrc,
                           const CanvasPen &pen,
                           const CanvasBrush &brush)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::RRect;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    /// ## Max values is 10
    ret.data      = {
        rrc.rect.x,
        rrc.rect.y,
        rrc.rect.width,
        rrc.rect.height,
        rrc.radius.leftRad,
        rrc.radius.topRad,
        rrc.radius.rightRad,
        rrc.radius.bottomRad
    };
    ret.pen       = pen;
    ret.brush     = brush;

    m_shapes.push_back( ret );
}

void CanvasBase::drawCircle(x_real xx,
                            x_real yy,
                            x_real rad,
                            const CanvasPen &pen,
                            const CanvasBrush &brush)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::Circle;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    /// ## Max values is 10
    ret.data      = {xx,yy,rad};
    ret.pen       = pen;
    ret.brush     = brush;

    m_shapes.push_back( ret );
}

void CanvasBase::drawCanvasPath(const CanvasPath &path,
                                const CanvasPen &pen,
                                const CanvasBrush &brush)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::Path;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    ret.path      = path;
    ret.pen       = pen;
    ret.brush     = brush;

    m_shapes.push_back( ret );
}

void CanvasBase::drawSimpleText(const x_string &text,
                                const Font &fnt,
                                const x_rect &rc,
                                const CanvasPen &pen)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::Text;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    /// ## Max values is 10
    ret.data      = {rc.x,rc.y,rc.width,rc.height};
    ret.text      = text;
    ret.format.font = fnt;

    ret.pen       = pen;
    m_shapes.push_back( ret );
}

void CanvasBase::drawSimpleText(const x_string &text,
                                const TextFormat &format,
                                const CanvasPen &pen)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::Text;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    ret.text      = text;
    ret.format    = format;

    ret.pen       = pen;
    m_shapes.push_back( ret );
}

void CanvasBase::drawImage(const x_string &source,
                           const x_size &size)
{
    CanvasShape ret;
    ret.type      = CanvasShapeType::Image;
    ret.antiAlias = m_antialias;
    ret.matrix    = m_matrix;
    ret.text      = source;
    ret.data      = {0,0,size.width,size.height};

    m_shapes.push_back( ret );
}

bool CanvasBase::antialias() const
{
    return m_antialias;
}

void CanvasBase::setAntialias(bool newAntialias)
{
    m_antialias = newAntialias;
}

filament::Engine *CanvasBase::filamentEngine() const
{
    return m_windowItem->filamentEngine();
}


filament::Scene *CanvasBase::filamentScene() const
{
    return m_filamentScene;
}

x_matrix4x4 CanvasBase::matrix() const
{
    return m_matrix;
}

void CanvasBase::setMatrix(const x_matrix4x4 &newMatrix)
{
    m_matrix = newMatrix;
}

PixelAlphaType CanvasBase::pixelAlphaType(SDL_PixelFormat sdlPxFormat,
                                          const SDL_PixelFormatDetails *sdlPxDetails)
{
    PixelAlphaType alphaType =
        sdlPxDetails->Amask == 0 ? PixelAlphaType::Opaque : PixelAlphaType::Unpremul;

    if( SDL_ISPIXELFORMAT_ALPHA(sdlPxFormat)){
        dbg_warning() << "This does not check for Premul Alpha Type";
        alphaType = PixelAlphaType::Unpremul;
    }
    else
        alphaType = PixelAlphaType::Opaque;

    return alphaType;
}


SDL_Surface *CanvasBase::updateSDLSurface()
{
    auto ret = SDL_GetWindowSurface( m_windowItem->sdlWindow() );
    return ret;
}

SDL_Texture *CanvasBase::updateSDLTexture(const x_size &sz)
{
    x_real ww=0;
    x_real hh=0;
    const auto res = m_sdlTexture &&
                     SDL_GetTextureSize( m_sdlTexture, &ww, &hh ) &&
                     (static_cast<int>(ww) == static_cast<int>(sz.width)) &&
                     (static_cast<int>(hh) == static_cast<int>(sz.height));


    if( res )
        return m_sdlTexture;

    if( m_sdlTexture )
        SDL_DestroyTexture( m_sdlTexture );

    m_sdlTexture = SDL_CreateTexture(
        m_windowItem->sdlRenderer(),
        SDL_PIXELFORMAT_XRGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        sz.width,
        sz.height);

    /// SDL_PIXELFORMAT_ARGB8888

    return m_sdlTexture;
}


}
