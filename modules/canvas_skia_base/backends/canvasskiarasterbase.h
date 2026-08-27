#ifndef CANVASSKIARASTERBASE_H
#define CANVASSKIARASTERBASE_H


#include "canvasskiabase.h"



namespace Qx::prv
{


class CanvasSkiaRasterBase : public CanvasSkiaBase
{
public:
    CanvasSkiaRasterBase(GraphicsWindow *winItm):
        Qx::prv::CanvasSkiaBase{ winItm }
    {
        m_canvasTarget = CanvasTarget::None;
    }
    virtual BackendResult initBackend(const x_size &sz) override
    {
        // m_skiaSurface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(10, 10));
        return BackendResult::SUCCESS;
    }
    virtual BackendResult renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp) override
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
};


}


#endif // CANVASSKIARASTERBASE_H
