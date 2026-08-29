#ifndef CANVASSKIARASTERSURFACE_H
#define CANVASSKIARASTERSURFACE_H


#include <backends/canvasskiarasterbase.h>



namespace Qx::Backend
{


class CanvasSkiaRasterSurface : public CanvasSkiaRasterBase
{
public:
    CanvasSkiaRasterSurface(prv::GraphicsWindow *winItm);
};


}


#endif // CANVASSKIARASTERSURFACE_H
