#ifndef CANVASSKIAOPENGLSURFACE_H
#define CANVASSKIAOPENGLSURFACE_H


#include <backends/canvasskiaopenglbase.h>



namespace Qx::Backend
{


class CanvasSkiaOpenGLSurface : public CanvasSkiaOpenGLBase
{
public:
    CanvasSkiaOpenGLSurface(prv::GraphicsWindow *winItm);
};


}


#endif // CANVASSKIAOPENGLSURFACE_H
