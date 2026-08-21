#include "screen.h"


namespace Qx
{

Screen::Screen(SDL_Window *window):
    m_size{}
{
    const auto dispID = SDL_GetDisplayForWindow( window );
    const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(dispID);

    if (mode){
        m_size.width  = mode->w;
        m_size.height = mode->h;
    }
}


x_size Screen::size() const
{
    return m_size;
}

x_real Screen::sizeRatio() const
{
    return m_size.width / m_size.height;
}

}
