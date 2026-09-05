#ifndef PLATFROM_H
#define PLATFROM_H

#include <SDL3/SDL_video.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <psapi.h>
#endif


namespace Qx::prv
{

class Platfrom
{
    Platfrom(){}


public:
    static void *nativeWindowHandle(SDL_Window *sdlWin)
    {
        const auto prpID = SDL_GetWindowProperties( sdlWin );
        return SDL_GetPointerProperty( prpID,
                                      SDL_PROP_WINDOW_WIN32_HWND_POINTER,
                                      NULL);
    }


#if defined(_WIN32) || defined(_WIN64)
    static SIZE_T ramUsage() {
        PROCESS_MEMORY_COUNTERS_EX  pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
            return (pmc.WorkingSetSize / 1024) / 1024;
        }
        return 0;
    }
#endif

};

}

#endif // PLATFROM_H
