#ifndef HOSTENV_H
#define HOSTENV_H


#include <misc/defs.h>
#include <misc/debug.h>


#include <SDL3/SDL_filesystem.h>
#include <algorithm>



namespace Qx::HostEnv {

using     x_path = x_string;



static inline x_string cnstRefToStr( const char *ref, SDL_Folder folder )
{
    dbg_assert( ref ) << "Trying to access a not existing OS path"
                   " with SDL_Folder value: " + std::to_string( folder );
    x_string ret{ ref };
    std::replace(ret.begin(), ret.end(), '\\', '/');
    return ret;
}

static inline x_string refToStr( char *ref, SDL_Folder folder )
{
    const auto ret = cnstRefToStr( ref, folder );
    SDL_free( ref );
    return ret;
}


struct App
{
    // static inline const x_path fonts   = "app:/fonts/";
    // static inline const x_path shaders = "core:/shaders/";

    // static inline constexpr x_path assetShader( const x_string &shdFile )
    // {
    //     return shaders + "compiled/" + shdFile;
    // }
    // static inline constexpr x_path font( const x_string &fntFile )
    // {
    //     return fonts + fntFile;
    // }

    // static inline constexpr x_path app()
    // {
    //     return cnstRefToStr( SDL_GetBasePath(), SDL_FOLDER_COUNT );
    // }


    // static inline constexpr x_path app( const x_string &flName )
    // {
    //     return app() + "/" + flName;
    // }


    // static inline constexpr x_path assetFile( const x_string &fileName )
    // {
    //     return shaders + "compiled/" + shdFile;
    // }


    static inline void setOrgName( const x_string &str )
    {
        dbg_assert( m_orgName.empty() ) << "org name can only be set once at uimain.h SDL_AppInit";
        m_orgName = str;
    }
    static inline void setAppName(const x_string &str)
    {
        dbg_assert( m_appName.empty() ) << "app name can only be set once at uimain.h SDL_AppInit";
        m_appName = str;
    }

    static inline constexpr x_string orgName()
    {
        return m_orgName;
    }

    static inline constexpr x_string appName()
    {
        return m_appName;
    }

    static inline constexpr x_string path()
    {
        return "NOT supported yet (.exe)";
    }

private:

    friend class UIApplication;
    static x_string m_orgName;
    static x_string m_appName;

};

struct OS
{

    static unsigned int cpuCoreCount();
    static inline constexpr x_string name()
    {
        return "NOT supported yet (Windows)";
    }

    static inline constexpr x_string arch()
    {
        return "NOT supported yet (x64)";
    }

    static inline constexpr x_string systemFonts()
    {
        return "C:/Windows/Fonts/";
    }
};

struct User
{
    static inline constexpr x_path name()
    {
        return "NOT supported yet (User)";
    }
    /// ## ------------------------------------------------------------
    ///
    static inline x_path data()
    {
        const auto org = Qx::HostEnv::App::orgName();
        const auto app = Qx::HostEnv::App::appName();
        return refToStr( SDL_GetPrefPath( org.data() , app.data() ), SDL_FOLDER_COUNT );
    }

    static inline x_path data( const x_string &flName )
    {
        return data() + flName;
    }

    static inline x_path dbProfile()
    {
        return data( "dbProfile.sqlite" );
    }

    // static inline x_path binProfile()
    // {
    //     return data( "user_profile.bin" );
    // }

    // static inline x_path jsonProfile()
    // {
    //     return data( "user_profile.json" );
    // }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path home()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_HOME ), SDL_FOLDER_HOME );
    }

    static inline x_path home( const x_string &flName )
    {
        return home() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path desktop()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_DESKTOP ), SDL_FOLDER_DESKTOP );
    }

    static inline x_path desktop( const x_string &flName )
    {
        return desktop() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path documents()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_DOCUMENTS ), SDL_FOLDER_DOCUMENTS );
    }

    static inline x_path documents( const x_string &flName )
    {
        return documents() + flName;
    }


    /// ## ------------------------------------------------------------
    ///
    static inline x_path downloads()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_DOWNLOADS ), SDL_FOLDER_DOWNLOADS );
    }

    static inline x_path downloads( const x_string &flName )
    {
        return downloads() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path music()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_MUSIC ), SDL_FOLDER_MUSIC );
    }

    static inline x_path music( const x_string &flName )
    {
        return music() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path pictures()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_PICTURES ), SDL_FOLDER_PICTURES );
    }

    static inline x_path pictures( const x_string &flName )
    {
        return pictures() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path publicShare()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_PUBLICSHARE ), SDL_FOLDER_PUBLICSHARE );
    }

    static inline x_path publicShare( const x_string &flName )
    {
        return publicShare() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path savedGames()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_SAVEDGAMES ), SDL_FOLDER_SAVEDGAMES );
    }

    static inline x_path savedGames( const x_string &flName )
    {
        return savedGames() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path screenShots()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_SCREENSHOTS ), SDL_FOLDER_SCREENSHOTS );
    }

    static inline x_path screenShots( const x_string &flName )
    {
        return screenShots() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path templates()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_TEMPLATES ), SDL_FOLDER_TEMPLATES );
    }

    static inline x_path templates( const x_string &flName )
    {
        return templates() + flName;
    }

    /// ## ------------------------------------------------------------
    ///
    static inline x_path videos()
    {
        return cnstRefToStr( SDL_GetUserFolder( SDL_FOLDER_VIDEOS ), SDL_FOLDER_VIDEOS );
    }

    static inline x_path videos( const x_string &flName )
    {
        return videos() + flName;
    }

};


}


#endif // HOSTENV_H
