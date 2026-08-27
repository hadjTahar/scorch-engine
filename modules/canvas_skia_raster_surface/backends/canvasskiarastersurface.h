#ifndef CANVASSKIARASTERSURFACE_H
#define CANVASSKIARASTERSURFACE_H


#include "../../canvas_skia_base/skia_base.h"



namespace Qx::prv
{


class CanvasSkiaRasterSurface : public SkiaBase
{
public:
    CanvasSkiaRasterSurface(GraphicsWindow *winItm);
    virtual BackendResult initBackend(const x_size &sz) override;
    virtual BackendResult renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp) override;
};


}


#endif // CANVASSKIARASTERSURFACE_H
