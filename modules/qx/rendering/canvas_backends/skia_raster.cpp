#include "skia_raster.h"



namespace Qx::prv
{


SkiaRASTER::SkiaRASTER( GraphicsWindow *winItm,
                       filament::Scene *filamentScn):
    Qx::prv::SkiaBase{ winItm, filamentScn }
{
}

BackendResult SkiaRASTER::initBackend(const x_size &sz)
{
    // m_skiaSurface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(10, 10));
    return BackendResult::SUCCESS;
}

BackendResult SkiaRASTER::renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp)
{
    const auto ww = m_skiaSurface? m_skiaSurface->width() : 0;
    const auto hh = m_skiaSurface? m_skiaSurface->height() : 0;
    const auto sameSize = (ww == sz.width) && (hh == sz.height);
    if( !sameSize )
    {
        const auto pxPair = helpers::skiaSdlPXFormats(pxFormat,pxAlphaTp);
        m_skiaSurface = SkSurfaces::Raster(
            SkImageInfo::Make(sz.width,
                                 sz.height,
                                 pxPair.colorType,
                                 pxPair.alphaType)
            );
        dbg_assert( m_skiaSurface.get() ) <<
            "Invalid SkSurface";
        m_skiaCanvas = m_skiaSurface->getCanvas();
        dbg_assert( m_skiaSurface.get() ) << "Invalid SkCanvas";
    }
    drawSkiaShapes();
    return BackendResult::SUCCESS;
}




}
