#ifndef SDL_MAIN_H
#define SDL_MAIN_H
#define SDL_MAIN_USE_CALLBACKS

#if defined( QX_DEF_INC_COMPILED_ASSETS )
#include "compiled_assets/compiled_assets.h"
#endif

#include <misc/hostenv.h>
#include <misc/assets.h>

#include <SDL3/SDL_main.h>
#include <memory>



namespace {

inline static std::unique_ptr<ApplicationType>  appInstance = nullptr;

/// ## ---------------------------------------------------------------------

#define QX_DEF_SDL_EXTERN extern "C"

QX_DEF_SDL_EXTERN SDLMAIN_DECLSPEC SDL_AppResult SDLCALL SDL_AppInit(void **appstate, int argc, char *argv[])
{
#if defined( QX_DEF_INC_COMPILED_ASSETS )
    // Qx::prv::AssetsStream::CompiledDataMap =  &Qx::prv::CompiledDataMap;
    Qx::Assets::setDataMap( &Qx::prv::CompiledDataMap );
#endif
    Qx::Assets::setAppSrcDir( QX_DEF_APP_SRC );

    Qx::HostEnv::App::setOrgName( QX_DEF_ORG_NAME );
    Qx::HostEnv::App::setAppName( QX_DEF_APP_NAME );
    appInstance = Qx::prv::CoreItem::addRootItem<ApplicationType>();
    return static_cast<SDL_AppResult>( appInstance->init( appstate, argc, argv ) );
}

QX_DEF_SDL_EXTERN SDLMAIN_DECLSPEC SDL_AppResult SDLCALL SDL_AppIterate(void *appstate)
{
    return static_cast<SDL_AppResult>( appInstance->iterate( appstate ) );
}

QX_DEF_SDL_EXTERN SDLMAIN_DECLSPEC SDL_AppResult SDLCALL SDL_AppEvent(void *appstate, SDL_Event *event)
{
    return static_cast<SDL_AppResult>( appInstance->event( appstate, event ) );
}

QX_DEF_SDL_EXTERN SDLMAIN_DECLSPEC void SDLCALL SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    const auto res = static_cast<Qx::prv::AppResult>( result );
    appInstance->quit( appstate, res );
    appInstance.reset();
}

}

#endif // SDL_MAIN_H
