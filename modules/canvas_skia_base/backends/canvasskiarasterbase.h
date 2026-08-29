#ifndef CANVASSKIARASTERBASE_H
#define CANVASSKIARASTERBASE_H


#include "canvasskiabase.h"



namespace Qx::Backend
{


class CanvasSkiaRasterBase : public CanvasSkiaBase
{
public:
    CanvasSkiaRasterBase(prv::GraphicsWindow *winItm):
        CanvasSkiaBase{ winItm }
    {
        m_canvasTarget = prv::CanvasTarget::None;
    }
    virtual prv::BackendResult initBackend(const x_size &sz) override
    {
        // m_skiaSurface = SkSurfaces::Raster(SkImageInfo::MakeN32Premul(10, 10));
        return prv::BackendResult::SUCCESS;
    }
    virtual prv::BackendResult renderShapes(const x_size &sz,
                                       prv::PixelFormat pxFormat,
                                       prv::PixelAlphaType pxAlphaTp) override
    {
        const auto ww = m_skiaSurface? m_skiaSurface->width() : 0;
        const auto hh = m_skiaSurface? m_skiaSurface->height() : 0;
        const auto sameSize = (ww == sz.width) && (hh == sz.height);
        if( !sameSize )
        {
            const auto pxPair = prv::helpers::skiaSdlPXFormats(pxFormat,pxAlphaTp);
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

        return prv::BackendResult::SUCCESS;
    }
};


}


#endif // CANVASSKIARASTERBASE_H
