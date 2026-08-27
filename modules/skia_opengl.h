#ifndef SKIA_OPENGL_H
#define SKIA_OPENGL_H



#include <skia/include/gpu/ganesh/gl/GrGLInterface.h>





#include "skia_base.h"

namespace Qx::prv
{


class SkiaOPENGL : public SkiaBase
{
public:
    SkiaOPENGL(SDL_Window *sdlWin, filament::Scene *filScn);
    virtual BackendResult initBackend(const x_size &sz) override;
    virtual BackendResult renderShapes(const x_size &sz,
                                       PixelFormat pxFormat,
                                       PixelAlphaType pxAlphaTp) override;
private:
    sk_sp<const GrGLInterface>  m_skiaInterface;
};

}


#endif // SKIA_OPENGL_H
