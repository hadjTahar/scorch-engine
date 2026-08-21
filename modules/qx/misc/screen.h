#ifndef SCREEN_H
#define SCREEN_H


#include "vecs.h"
#include <SDL3/SDL_video.h>


namespace Qx
{

namespace prv
{
class WindowItem;
}


class Screen
{

    friend class prv::WindowItem;


protected:
    Screen(SDL_Window *window);

public:
    x_size size() const;
    x_real sizeRatio() const;


protected:

    x_size m_size;

};


}
#endif // SCREEN_H
