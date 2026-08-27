#ifndef CANVASSKIARASTERTEXTURE_H
#define CANVASSKIARASTERTEXTURE_H


#include "../../canvas_skia_base/skia_base.h"



namespace Qx::prv
{


class CanvasSkiaRasterTexture : public SkiaBase
{
public:
    CanvasSkiaRasterTexture(GraphicsWindow *winItm);
    virtual BackendResult initBackend(const x_size &sz) override;
    virtual BackendResult renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp) override;
};


}


#endif // CANVASSKIARASTERTEXTURE_H
