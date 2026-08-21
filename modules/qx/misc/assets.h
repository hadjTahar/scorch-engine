#ifndef ASSETS_H
#define ASSETS_H

#include <misc/debug.h>
#include <misc/defs.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_filesystem.h>

#include <map>
#include <set>
#include <algorithm>


namespace Qx
{
struct Assets;
}

namespace Qx::prv
{

class AssetsStream
{

    friend struct Qx::Assets;

protected:
    AssetsStream(const x_dataSpan &bin );
    AssetsStream(const x_string &fileName);
    AssetsStream() = delete;
    AssetsStream(const AssetsStream&) = delete;
    AssetsStream& operator=(const AssetsStream&) = delete;
    AssetsStream(AssetsStream&&) = delete;
    AssetsStream& operator=(AssetsStream&&) = delete;

public:
    ~AssetsStream();
    const x_string   dataText() const;

    /// ## Either x_data or x_dataSpan
    const auto data() const
    {
        if constexpr( QX_DEF_USE_COMPILED_ASSETS )
            return dataSpan();

        else if constexpr( !QX_DEF_USE_COMPILED_ASSETS )
            return dataCopy();
    }

    template< class Type>
    const auto data_copy_cast() const
    {
        const auto dt = dataCopy();
        std::vector<Type> ret(dt.begin(), dt.end());
        return ret;
    }



protected:
    const x_data     dataCopy() const;
    const x_dataSpan dataSpan() const;




protected:
    static std::map<std::string, const x_dataSpan> const *CompiledDataMap;
    static x_string appSrcDir;
    static AssetsStream load(const  x_string &fileName);
    static bool         check(const x_string &fileName);



    static x_string correctPath(const x_string &fileName);

    template< class Type>
    inline Type readFile( SDL_IOStream *handle ) const;
    void clearIOStream();

protected:
    x_dataSpan     m_span;
    x_string       m_fileName;
    SDL_IOStream  *m_handle;
};



/// ## -----------------------------------------------------------------------
/// ## -----------------------------------------------------------------------
///

template<class Type>
Type AssetsStream::readFile(SDL_IOStream *handle) const
{
    Type ret;
    if (!handle) {
        dbg_print() << "Could not open file " << " - " << SDL_GetError();
        return ret;
    }

    // Determine the file size
    const auto size = static_cast<x_count>( SDL_GetIOSize(handle) );
    if (size < 0) {
        dbg_print() << "Could not read file size " << SDL_GetError();
        return ret;
    }

    // Allocate a buffer with the required size
    ret.resize( size, 0 );

    // Read the file content into the buffer
    const auto BytesRead = SDL_ReadIO( handle, &ret[0], size );
    if (BytesRead != size) {
        dbg_print() << "Could not read entire file " << SDL_GetError();
        return ret;
    }
    return ret;
}

}



/// ## -----------------------------------------------------------------------
/// ## -----------------------------------------------------------------------
///

namespace Qx
{
struct Assets
{
    static inline auto load(const x_string &fileName)
    {
        return prv::AssetsStream::load( fileName);
    }

    static inline void setDataMap( std::map<std::string, const x_dataSpan> const * const dtMap )
    {
        dbg_assert( !Qx::prv::AssetsStream::CompiledDataMap ) <<
            "Qx::prv::AssetsStream::CompiledDataMap is already set";
        Qx::prv::AssetsStream::CompiledDataMap =  dtMap;
    }

    static inline void setAppSrcDir( const x_string &srcDir )
    {
        dbg_assert( Qx::prv::AssetsStream::appSrcDir.empty() ) <<
            "Qx::prv::AssetsStream::appSrcDir is already set";
        Qx::prv::AssetsStream::appSrcDir =  srcDir;
    }

    static std::vector<std::string> fileNames( x_string dir)
    {
        std::vector<std::string> files;
        const bool isAsset = dir.starts_with( ":/" );
        if ( isAsset && QX_DEF_USE_COMPILED_ASSETS ){
            if (!dir.empty() && dir.back() != '/') {
                dir += '/';
            }
            for (const auto& [path, data] : *Qx::prv::AssetsStream::CompiledDataMap) {
                if (path.find(dir) == 0) {
                    std::string remainder = path.substr(dir.length());

                    // Ensure there are no more slashes (this keeps it to the current dir only)
                    if (!remainder.empty() && remainder.find('/') == std::string::npos) {
                        files.push_back(dir + remainder);
                    }
                }
            }
        }
        else
        {
            const auto newDir = prv::AssetsStream::correctPath( dir );
            const auto res = SDL_EnumerateDirectory(newDir.c_str(), EnumFileCallback, &files);
            dbg_assert( res ) << "SDL could not enumurate folder: " << dir;
        }
        return files;
    }



    static SDL_EnumerationResult SDLCALL EnumFileCallback(void *userdata,
                                                          const char *dirname,
                                                          const char *fname) {
        auto *files = static_cast<std::vector<std::string> *>(userdata);
        std::string cleanDir = dirname;
        std::replace(cleanDir.begin(), cleanDir.end(), '\\', '/');


        std::string fullPath = std::string(cleanDir) + std::string(fname);
        SDL_PathInfo info;
        const auto res = SDL_GetPathInfo(fullPath.c_str(), &info) && info.type == SDL_PATHTYPE_FILE;
        if (res)
            files->push_back( cleanDir + fname);

        return SDL_ENUM_CONTINUE; // Keep going until all files are found
    }

};

}
#endif // ASSETS_H
