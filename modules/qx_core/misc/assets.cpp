#include "assets.h"
#include <regex>
#include <SDL3/SDL_filesystem.h>


namespace Qx::prv
{

x_string AssetsStream::appSrcDir = "";
std::map<std::string, const x_dataSpan> const *AssetsStream::CompiledDataMap = nullptr;


AssetsStream::AssetsStream(const x_dataSpan &bin):
    m_span{ bin },
    m_fileName{ "" },
    m_handle{ nullptr}
{
    m_handle = SDL_IOFromConstMem( m_span.data(), m_span.size() );
}


AssetsStream::AssetsStream(const x_string &fileName):
    m_span{},
    m_fileName{ fileName },
    m_handle{ nullptr}
{
    m_handle = SDL_IOFromFile( m_fileName.c_str(), "rb" );
}

AssetsStream::~AssetsStream()
{
    clearIOStream();
}



const x_string AssetsStream::dataText() const
{
    dbg_assert( m_handle) << "Can't read a null m_handle from file: " + m_fileName;
    if( !m_fileName.empty() )
        return readFile<x_string>( m_handle );
    else if( m_span.data() )
        return readFile<x_string>( m_handle );
    dbg_assert( false ) << "At least one should be valid";
    return "";
}

const x_data AssetsStream::dataCopy() const
{
    dbg_assert( m_handle ) << "Can't read a null m_handle from file: " + m_fileName;
    if( !m_span.empty() )
        dbg_tips() << "Memory data is valid "
                      "Use AssetsStream::dataRef instead, "
                      "Don't forget to check if valid before usage";
    if( !m_fileName.empty() )
        return readFile<x_data>( m_handle );
    else if( m_span.data() )
        return readFile<x_data>( m_handle );
    dbg_assert( false ) << "At least one should be valid";
    return {};
}

const x_dataSpan AssetsStream::dataSpan() const
{
    dbg_assert( !m_span.empty() ) << "Empty m_span";
    return m_span;
}

AssetsStream AssetsStream::load(const x_string &fileName)
{
    const bool isAsset = fileName.starts_with( ":/" );
    if ( isAsset && QX_DEF_USE_COMPILED_ASSETS ){
        dbg_assert( AssetsStream::CompiledDataMap ) << "AssetsStream::CompiledDataMap is null";

        const auto res = check( fileName );
        dbg_assert( res ) << "Could not find compiled asset";
        const auto &dtMap = *AssetsStream::CompiledDataMap;
        if( res )
            return AssetsStream{ dtMap.at( fileName ) };
        return AssetsStream{ x_dataSpan{} };
    }
    else{
        /// ## Otherwise it's a normal file
        /// ## or we are not using a compiled asset
        const auto newFileName = correctPath( fileName );
        check( newFileName );
        // return AssetsStream( correctPath(newFileName) );
        return AssetsStream{ newFileName };
    }
    return AssetsStream{ "" };

}

bool AssetsStream::check(const x_string &fileName)
{
    bool ret = false;
    const bool isAsset = fileName.starts_with( ":/" );
    if ( isAsset && QX_DEF_USE_COMPILED_ASSETS ){
        dbg_assert( AssetsStream::CompiledDataMap ) << "AssetsStream::CompiledDataMap is null";
        const auto &dtMap = *AssetsStream::CompiledDataMap;
        ret = AssetsStream::CompiledDataMap && dtMap.contains( fileName );
    }
    else
        ret = SDL_GetPathInfo( fileName.data(), NULL);

    dbg_assert( ret ) <<
        "Could not find file: " <<
        fileName;

    return ret;
}

x_string AssetsStream::correctPath(const x_string &fileName)
{
    const bool isAsset = fileName.starts_with( ":/" );
    auto newFileName = fileName;


    if( isAsset ){
        const auto path = appSrcDir + "/assets/";
        return std::regex_replace(newFileName,
                                  std::regex(":/"),
                                   path);
    }

    return fileName;
}

void AssetsStream::clearIOStream()
{
    if( !m_handle )
        return;
    SDL_CloseIO( m_handle );
    m_handle = nullptr;
}

}
