#ifndef SCREEN_H
#define SCREEN_H


#include "vecs.h"
#include <SDL3/SDL_video.h>


namespace Qx
{

namespace prv
{
class GraphicsWindow;
class GraphicsCamera;
}


class Screen
{

    friend class prv::GraphicsWindow;
    friend class prv::GraphicsCamera;


protected:
    Screen();
    Screen(SDL_Window *window);

public:
    x_size size() const;
    x_real sizeRatio() const;


protected:

    x_size m_size;

};


}
#endif // SCREEN_H
