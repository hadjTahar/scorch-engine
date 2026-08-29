#ifndef CANVASSKIABASE_H
#define CANVASSKIABASE_H

#include "skia_helpers.h"

#include <canvas/canvasbase.h>
#include <core/graphicswindow.h>

#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkPictureRecorder.h>
#include <skia/include/core/SkPicture.h>
#include <skia/include/gpu/ganesh/gl/GrGLDirectContext.h>  // For GrDirectContexts
#include <skia/include/gpu/ganesh/GrDirectContext.h>
#include <skia/include/core/SkFontMgr.h>
#include <skia/include/gpu/ganesh/GrDirectContext.h>
#include <skia/include/core/SkTypeface.h>
#include <skia/include/ports/SkFontMgr_empty.h>
#include <skia/include/core/SkM44.h>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Qx::Backend
{


class CanvasSkiaBase : public prv::CanvasBase
{
    friend class GraphicsScene;

public:
    CanvasSkiaBase( prv::GraphicsWindow *winItm):
        prv::CanvasBase{winItm},
        m_skiaCanvas{ nullptr },
        m_skiaFontsManager{SkFontMgr_New_Custom_Empty()}
    {
        dbg_static_assert_same_types(x_real,SkScalar);
        dbg_static_assert_same_types(x_vector2,SkPoint);
        dbg_static_assert_same_types(SkColor4f,x_rgba);

        dbg_static_assert_same_types(prv::CanvasPen::StrokeCap,SkTileMode);
        dbg_static_assert_same_types(prv::CanvasPen::StrokeJoin,SkPaint::Join);
        dbg_static_assert_same_types(Qx::prv::PathVerb,SkPathVerb);
        dbg_static_assert_same_types(Qx::CanvasPath::FillType,SkPathFillType);
        loadFontsDB();

    }
    void snapshot( const std::string &flName )
    {
        if( !m_skiaSurface )
            return;
        // auto image = m_skiaSurface->makeImageSnapshot();
        // // Encode to PNG
        // SkPngEncoder::Options options;
        // options.fZLibLevel = 9;

        // auto png = SkPngEncoder::Encode(
        //     m_skiaContext.get(),
        //     image.get(),
        //     options
        //     );

        // // Write to file
        // std::ofstream out(flName, std::ios::binary);
        // out.write((const char*)png->data(), png->size());
    }

protected:
    void drawSkiaShapes()
    {

        if( !m_skiaCanvas )
            return;

        m_skiaCanvas->clear(SK_ColorWHITE);
        // m_skiaCanvas->clear(SK_ColorTRANSPARENT);
        for ( const auto &shp : m_shapes) {
            m_skiaCanvas->save();
            m_skiaCanvas->concat( SkM44::ColMajor( glm::value_ptr(shp.matrix) ) );

            const auto shpTp = shp.type;

            switch (shpTp) {
            case prv::CanvasShapeType::Rect:{
                prv::helpers::drawRect( m_skiaCanvas, shp );
                break;
            }
            case prv::CanvasShapeType::RRect:{
                prv::helpers::drawRRect( m_skiaCanvas, shp );
                break;
            }
            case prv::CanvasShapeType::Circle:{
                prv::helpers::drawCircle( m_skiaCanvas, shp );
                break;
            }
            case prv::CanvasShapeType::Path:{
                prv::helpers::drawPath( m_skiaCanvas, shp );
                break;
            }
            case prv::CanvasShapeType::Text:{
                prv::helpers::drawSimpleText( m_skiaCanvas, shp );
                break;
            }
            case prv::CanvasShapeType::Image:{
                prv::helpers::drawImage( m_skiaCanvas, shp );
                break;
            }

            default:
                dbg_assert( false )<< "Shape type: "
                                  << static_cast<int>( shpTp)
                                  << "not supported yet";
                break;
            }

            m_skiaCanvas->restore();

        }
    }

protected:
    void presentToSurface(SDL_Surface *sdlSurface,
                          const x_size &sz) override final
    {
        if( !m_skiaSurface )
            return;
        if( !sdlSurface )
            return;

        const SkImageInfo imgInfo = m_skiaSurface->imageInfo();

        // Make sure SDL_Surface is not locked before accessing its pixels.
        if (SDL_MUSTLOCK(sdlSurface))
            SDL_LockSurface(sdlSurface);

        SkPixmap pixmap;
        const auto ok = m_skiaSurface->peekPixels(&pixmap);
        if( ok )
        {
            const size_t size = pixmap.rowBytes() * pixmap.height();
            memcpy(
                sdlSurface->pixels,
                pixmap.addr(),
                size
                );
        }
        else{
            dbg_error() << "m_skiaSurface can't peekPixels into SDL_Surface, trying readPixels ....";

            bool retryOk = m_skiaSurface->readPixels(
                imgInfo,
                sdlSurface->pixels,
                sdlSurface->pitch,
                0,
                0
                );

            if( !retryOk )
                dbg_error() << "m_skiaSurface can't read pixels into SDL_Surface";
        }


        if (SDL_MUSTLOCK(sdlSurface))
            SDL_UnlockSurface(sdlSurface);
        SDL_UpdateWindowSurface( m_windowItem->sdlWindow() );
    }
    void presentToTexture(SDL_Texture *sdlTexture,
                          SDL_Renderer *sdlRenderer,
                          const x_size &sz) override final
    {
        if( !m_skiaSurface )
            return;
        SkPixmap pixmap;
        const auto ok = m_skiaSurface->peekPixels(&pixmap);
        if( ok ){
            SDL_UpdateTexture(
                sdlTexture,
                nullptr,
                pixmap.addr(),
                static_cast<int>(pixmap.rowBytes()));
        }
        else{
            dbg_warning() << "m_skiaSurface can't read peekPixels into SDL_Texture, trying readPixels ....";

            const SkImageInfo imgInfo = m_skiaSurface->imageInfo();
            std::vector<uint8_t> pixels(
                imgInfo.computeMinByteSize()
                );

            bool retryOk = m_skiaSurface->readPixels(
                imgInfo,
                pixels.data(),
                imgInfo.minRowBytes(),
                0,
                0
                );
            SDL_UpdateTexture(
                m_sdlTexture,
                nullptr,
                pixels.data(),
                imgInfo.minRowBytes()
                );
            if( !retryOk )
                dbg_error() << "m_skiaSurface can't read pixels into SDL_Texture";
        }



        SDL_RenderClear(sdlRenderer);
        SDL_RenderTexture(sdlRenderer, sdlTexture, nullptr, nullptr);
        SDL_RenderPresent(sdlRenderer);

    }



protected:
    void loadFontsDB()
    {
        /// ## ToDO: Use Qx::HostEnv::OS::systemFonts();
        dbg_warning() << "CanvasSkiaBase::loadFontsDB is not loading system fonts";
        const auto fontsNames = Qx::Assets::fileNames( ":/fonts" );

        dbg_info() << "Loading Skia Canvas fonts ... ";
        dbg_info() << "-------------------------------";
        for ( const auto &ftName : fontsNames) {

            dbg_info() << ftName;
            const auto fntData  = Qx::Assets::load( ftName ).data();
            const auto data     = prv::helpers::MakeSkData( fntData.data(), fntData.size() );
            const auto typeface = m_skiaFontsManager->makeFromData( data );

            SkString name;
            typeface->getFamilyName( &name );
            const x_string fntAlias{name.data()};

            Font fnt;
            fnt.familyName = fntAlias;
            fnt.bold       = typeface->isBold();
            fnt.italic     = typeface->isItalic();
            prv::helpers::m_typefaceList[fnt] = typeface;
        }

    }

protected:
    sk_sp<SkSurface>            m_skiaSurface;
    SkCanvas*                   m_skiaCanvas;
    sk_sp<GrDirectContext>      m_skiaContext;
    sk_sp<SkFontMgr>            m_skiaFontsManager;



};

}
#endif // CANVASSKIABASE_H
