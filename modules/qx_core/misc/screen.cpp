#include "screen.h"


namespace Qx
{

Screen::Screen():
    m_size{0,0,0},
    m_dpi{ 96 },
    m_simDpi{ 96 }
{
}

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

x_vector2 Screen::dpi() const
{
    return m_dpi;
}

x_vector2 Screen::dpiScale() const
{
    return {1,1};
    // return m_dpi/m_simDpi;
}

}
