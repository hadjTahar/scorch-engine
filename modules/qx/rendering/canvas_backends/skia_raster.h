#ifndef SKIA_RASTER_H
#define SKIA_RASTER_H


#include "skia_base.h"



namespace Qx::prv
{


class SkiaRASTER : public SkiaBase
{
public:
    SkiaRASTER(GraphicsWindow *winItm);
    virtual BackendResult initBackend(const x_size &sz) override;
    virtual BackendResult renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp) override;
};


}
namespace Qx
{
// using Canvas = prv::SkiaRASTER;

}

#endif // SKIA_RASTER_H
