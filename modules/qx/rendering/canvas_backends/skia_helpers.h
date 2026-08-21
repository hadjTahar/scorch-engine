#ifndef SKIA_HELPERS_H
#define SKIA_HELPERS_H

#include <map>
#include <misc/pixelformats.h>
#include <misc/debug.h>
#include <misc/debugprint.h>
#include <misc/assets.h>

#include <rendering/canvasshape.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_pixels.h>


#include <skia/include/core/SkCanvas.h>
#include <skia/include/effects/SkDashPathEffect.h>
#include <skia/include/effects/SkGradient.h>
#include <skia/include/core/SkRRect.h>
#include <skia/include/core/SkImage.h>

#include <skia/include/core/SkFont.h>
#include <skia/include/core/SkFontMetrics.h>
#include <skia/include/core/SkFontMetrics.h>
#include <skia/include/core/SkData.h>

namespace Qx::prv::helpers {


static inline std::map<Font, sk_sp<SkTypeface>> m_typefaceList{};

const auto MakeSkData = QX_DEF_USE_COMPILED_ASSETS?
                            SkData::MakeWithoutCopy :
                            SkData::MakeWithCopy;
struct SkiaPixelFormat
{
    SkColorType colorType;
    SkAlphaType alphaType;
};

static inline SkiaPixelFormat skiaSdlPXFormats(PixelFormat pxFormat,
                                        PixelAlphaType pxAlphaTp)
{
    SkiaPixelFormat ret;
    ret.alphaType = static_cast<SkAlphaType>( pxAlphaTp );


    switch (pxFormat)
    {
    case PixelFormat::XBGR8888:
        ret.colorType= kRGBA_8888_SkColorType;
        break;
    case PixelFormat::XRGB8888:
        ret.colorType= kBGRA_8888_SkColorType;
        break;

    case PixelFormat::RGB24:
        ret.colorType= kRGB_888x_SkColorType;
        break;
    default:
        dbg_assert( false )
            << "SDL color format "
            << std::hex << "0x" << static_cast<int>(pxFormat)
            << " not implemented yet";
        ret.colorType= kUnknown_SkColorType;
        break;
    }

    return ret;
}


/// ## ---------------------------------------------------


static inline SkPath skPath(const CanvasPath &path)
{
    const auto &pts = path.points();
    const auto &vrb = path.verbs();
    const auto &cnc = path.conics();

    const std::span<const SkPoint>     ptsSpan{ reinterpret_cast<SkPoint const*>(pts.data()), pts.size() };
    const std::span<const SkPathVerb>  vrbSpan{ reinterpret_cast<SkPathVerb const*>(vrb.data()), vrb.size() };
    const std::span<const SkScalar>    cncSpan{ reinterpret_cast<SkScalar const*>(cnc.data()), cnc.size() };

    const auto fillTP = static_cast<SkPathFillType>( path.fillType() );
    return SkPath::Raw(ptsSpan, vrbSpan, cncSpan, fillTP );
}

/// ## ---------------------------------------------------

static inline std::span<SkColor4f> skColorsSpan(const CanvasBrush &brush )
{
    std::span<SkColor4f> colorSpan(
        reinterpret_cast<SkColor4f*>(brush.colors().data()),
        brush.colors().size()
        );

    return colorSpan;
}

static inline std::span<SkScalar> skStopsSpan(const CanvasBrush &brush )
{
    return {brush.stops().data(), brush.stops().size()};
}

static inline SkTileMode skGradTile(const CanvasBrush &brush )
{
    return static_cast<SkTileMode>( brush.tileMode() );
}

/// ## ---------------------------------------------------

static inline sk_sp<SkShader> skLinearGradientShader(const CanvasBrush &brush)
{
    const auto colorsSpan  = skColorsSpan( brush );
    const auto tlMode      = skGradTile( brush );
    const SkGradient::Colors gradColors(colorsSpan,
                                        tlMode);
    const SkGradient grad( gradColors, SkGradient::Interpolation{} );

    const SkPoint pts[2] = {
        {brush.value(0), brush.value(1)},
        {brush.value(2), brush.value(3)}
    };
    return SkShaders::LinearGradient( pts, grad );
}



static inline sk_sp<SkShader> skRadialGradientShader(const CanvasBrush &brush)
{
    SkPoint  center  = SkPoint::Make( brush.value(0), brush.value(1));
    SkScalar radius  = brush.value(2);

    const auto colorsSpan   = skColorsSpan( brush );
    const auto stops        = skStopsSpan( brush );
    const auto tlMode       = skGradTile( brush );
    const SkGradient::Colors gradColors(colorsSpan,
                                        stops,
                                        tlMode);

    const SkGradient grad( gradColors, SkGradient::Interpolation{} );
    return SkShaders::RadialGradient(
        center,
        radius,
        grad);
}

static inline sk_sp<SkShader> skRadialConicalShader(const CanvasBrush &brush)
{
    const auto colorsSpan   = skColorsSpan( brush );
    const auto tlMode       = skGradTile( brush );

    const SkPoint  center  = SkPoint::Make( brush.value(0), brush.value(1));
    const SkScalar radius  = brush.value(2);

    const SkPoint  endCenter  = SkPoint::Make( brush.value(3), brush.value(4));
    const SkScalar endRadius  = brush.value(5);

    const SkGradient::Colors gradColors(colorsSpan,
                                        tlMode);
    const SkGradient grad( gradColors, SkGradient::Interpolation{} );
    return SkShaders::TwoPointConicalGradient(
        center,
        radius,
        endCenter,
        endRadius,
        grad
        );
}

static inline sk_sp<SkShader> skSweepConicalShader(const CanvasBrush &brush)
{
    const auto colorsSpan  = skColorsSpan( brush );
    const auto tlMode      = skGradTile( brush );

    const auto center      = SkPoint::Make( brush.value(0), brush.value(1));
    const auto startAngle  = brush.value(2);
    const auto endAngle    = brush.value(3);



    const SkGradient::Colors gradColors(colorsSpan,
                                        tlMode);
    const SkGradient grad( gradColors, SkGradient::Interpolation{} );
    return SkShaders::SweepGradient(
        center,
        startAngle,
        endAngle,
        grad
        );

}

/// ## ---------------------------------------------------

static inline SkPaint strokePaint( const CanvasShape &shp )
{
    const CanvasPen &pen = shp.pen;
    SkPaint retPaint;
    retPaint.setStyle(SkPaint::kStroke_Style);
    retPaint.setAntiAlias( shp.antiAlias );
    // retPaint.setColor( pen.color() );
    const auto clrLst = pen.color();
    retPaint.setColor4f( {clrLst[0], clrLst[1], clrLst[2], clrLst[3]} );
    retPaint.setStrokeWidth(pen.width() );


    const auto strkCap = static_cast<SkPaint::Cap>( pen.strokeCap() );
    const auto strkJoin = static_cast<SkPaint::Join>( pen.strokeJoin() );

    retPaint.setStrokeCap( strkCap );
    retPaint.setStrokeJoin( strkJoin );
    const auto pattern = pen.dashPattern();
    retPaint.setPathEffect( SkDashPathEffect::Make(pattern.pattern, pattern.phase) );
    return retPaint;
}

static inline SkPaint fillPaint( const CanvasShape &shp )
{
    SkPaint retPaint;
    retPaint.setStyle(SkPaint::kFill_Style);
    retPaint.setAntiAlias( shp.antiAlias );


    const auto &brush  = shp.brush;
    const auto brushTp = brush.type();

    switch ( brushTp ) {
    case CanvasBrush::BrushType::Solid:{
        const auto clrLst = brush.colorStop(0).color;
        retPaint.setColor4f( {clrLst[0], clrLst[1], clrLst[2], clrLst[3]} );
        break;
    }
    case CanvasBrush::BrushType::Linear:
        retPaint.setShader( skLinearGradientShader( brush ) );
        break;
    case CanvasBrush::BrushType::Radial:
        retPaint.setShader( skRadialGradientShader( brush ) );
        break;
    case CanvasBrush::BrushType::Conical:
        retPaint.setShader( skRadialConicalShader( brush ) );
        break;
    case CanvasBrush::BrushType::Sweep:
        retPaint.setShader( skSweepConicalShader( brush ) );
        break;
    default:
        dbg_assert( false ) << "Unsupported brush type: CanvasBrush::BrushType::" << static_cast<int>(brushTp);
        break;
    }

    return retPaint;
}

/// ## ---------------------------------------------------


static inline void drawRect( SkCanvas* canvas, const CanvasShape &shp)
{
    const x_rect rc  = {shp.data[0], shp.data[1], shp.data[2], shp.data[3]};
    const SkRect skRc = SkRect::MakeXYWH(rc.x, rc.y, rc.width, rc.height);
    canvas->drawRect( skRc, fillPaint( shp ) );
    canvas->drawRect( skRc, strokePaint( shp ) );
}

static inline void drawRRect( SkCanvas* canvas, const CanvasShape &shp)
{
    const x_rect rc  = {shp.data[0], shp.data[1], shp.data[2], shp.data[3]};
    const SkRect skRc = SkRect::MakeXYWH(rc.x, rc.y, rc.width, rc.height);


    SkRRect skRRC;
    skRRC.setNinePatch( skRc,
                       shp.data[4], /// ## Left
                       shp.data[5], /// ## Top
                       shp.data[6], /// ## Right
                       shp.data[7]  /// ## Bottom
                       );


    canvas->drawRRect( skRRC, fillPaint( shp ) );
    canvas->drawRRect( skRRC, strokePaint( shp ) );
}

static inline void drawCircle(SkCanvas* canvas, const CanvasShape &shp)
{
    const auto xx = shp.data[0];
    const auto yy = shp.data[1];
    const auto rd = shp.data[2];
    canvas->drawCircle( xx, yy, rd, fillPaint( shp ) );
    canvas->drawCircle( xx, yy, rd, strokePaint( shp ) );
}


static inline void drawPath( SkCanvas* canvas, const CanvasShape &shp)
{
    const x_rect rc  = {shp.data[0], shp.data[1], shp.data[2], shp.data[3]};
    const SkRect skRc = SkRect::MakeXYWH(rc.x, rc.y, rc.width, rc.height);
    canvas->drawRect( skRc, fillPaint( shp ) );
    canvas->drawRect( skRc, strokePaint( shp ) );

    const auto skPth = skPath( shp.path );
    canvas->drawPath(skPth, strokePaint( shp ) );
    canvas->drawPath(skPth, fillPaint( shp ) );
}



static inline sk_sp<SkTypeface> getTypeface(const Font &fnt)
{
    auto it = m_typefaceList.find(fnt);
    if ( it != m_typefaceList.end() )
        return it->second;
    dbg_warning() << "Could not find font : " << fnt;
    return SkTypeface::MakeEmpty();
}


static inline x_vector2 textPosition(const x_string &text,
                                     const SkFont &skFont,
                                     const x_rect &rc)
{
    const char* rawText = text.data();
    x_count len = strlen(rawText);
    // 1. Measure horizontal bounds
    SkRect textBounds;
    skFont.measureText(rawText, len, SkTextEncoding::kUTF8, &textBounds);

    // 2. Get vertical metrics for baseline adjustment
    SkFontMetrics metrics;
    skFont.getMetrics(&metrics);

    // Calculate X: Center of rect minus half the text width, adjusted for bearing
    x_real x = rc.x + (rc.width - textBounds.width()) * 0.5f - textBounds.fLeft;

    // Calculate Y: Center of rect minus the midpoint of the font's vertical span
    // (fAscent is typically negative, fDescent is positive)
    x_real verticalCenterOffset = (metrics.fAscent + metrics.fDescent) * 0.5f;
    x_real y = rc.y + (rc.height * 0.5f) - verticalCenterOffset;

    return {x, y}; // Returns your engine's point type
}

static inline x_vector2 textPosition(const x_string &text, const TextFormat &format)
{
    // 1. Setup Skia Font and Metrics
    SkFont skFont(getTypeface(format.font), format.font.pxSize);
    const char* rawText = text.data();
    x_count len = text.size();

    SkRect textBounds;
    skFont.measureText(rawText, len, SkTextEncoding::kUTF8, &textBounds);

    SkFontMetrics metrics;
    skFont.getMetrics(&metrics);

    x_vector2 pos;

    // --- Horizontal Alignment ---
    switch (format.hAlign) {
    case TextHAlign::Left:
        pos.x = format.rect.x - textBounds.fLeft;
        break;
    case TextHAlign::Center:
        pos.x = format.rect.x + (format.rect.width - textBounds.width()) * 0.5f - textBounds.fLeft;
        break;
    case TextHAlign::Right:
        pos.x = format.rect.width - textBounds.width() - textBounds.fLeft;
        break;
    case TextHAlign::Justify:
        // For simple text, Justify usually defaults to Left.
        // Full justification requires SkParagraph or manual word spacing.
        pos.x = format.rect.x - textBounds.fLeft;
        break;
    }

    // --- Vertical Alignment ---
    // Note: y coordinate in Skia drawSimpleText is the BASELINE.
    switch (format.vAlign) {
    case TextVAlign::Top:
        // Align the top of the 'ascenders' to the top of the rect
        pos.y = format.rect.y - metrics.fAscent;
        break;
    case TextVAlign::Middle:{
        // Calculate the visual midpoint of the font (ascent to descent)
        // and align it to the rect's center.
        x_real fontHeightMid = (metrics.fAscent + metrics.fDescent) * 0.5f;
        pos.y = format.rect.y + (format.rect.height * 0.5f) - fontHeightMid;
        break;
    }
    case TextVAlign::Bottom:
        // Align the bottom of the 'descenders' to the bottom of the rect
        pos.y = format.rect.height - metrics.fDescent;
        break;
    case TextVAlign::Baseline:
        // Draw directly on the rect's bottom (or a specific baseline)
        pos.y = format.rect.height;
        break;
    }

    return pos;
}



// static inline void drawSimpleText(const x_string &text,
//                               const Font &fnt,
//                               const x_rect &rc,
//                               const CanvasPen &pen)
// {
//     const SkFont  skFont(getTypeface( fnt ), fnt.pxSize);
//     const char*   rawText = text.data();
//     const auto pos = textPosition( text, skFont, rc );
//     m_skiaCanvas->drawSimpleText(rawText,
//                                  strlen(rawText),
//                                  SkTextEncoding::kUTF8,
//                                  pos.x,
//                                  pos.y,
//                                  skFont,
//                                  strokePaint( pen ));
// }

static inline void drawSimpleText( SkCanvas* canvas, const CanvasShape &shp)
{
    const x_string &text = shp.text;
    const TextFormat &format = shp.format;
    const CanvasPen &pen = shp.pen;

    const SkFont  skFont(getTypeface( format.font ), format.font.pxSize);
    const char*   rawText = text.data();
    const auto pos = textPosition( text, format );
    canvas->drawSimpleText(rawText,
                                 strlen(rawText),
                                 SkTextEncoding::kUTF8,
                                 pos.x,
                                 pos.y,
                                 skFont,
                                 strokePaint( shp ));
}

static inline void drawImage( SkCanvas* canvas, const CanvasShape &shp)
{
    const x_rect   &rc  = {shp.data[0], shp.data[1], shp.data[2], shp.data[3]};
    const x_string &source = shp.text;

    if( source.empty() )
        return;
    const auto imgFile = Assets::load( source );
    const auto imgData = imgFile.data();

    const auto data     = MakeSkData( imgData.data(), imgData.size() );
    if (!data)
        return;
    sk_sp<SkImage> image = SkImages::DeferredFromEncodedData( data );
    if (!image)
        return;

    const auto size = x_size{rc.width,rc.height,0};
    const auto originalSz = size.width < 0 || size.height < 0;
    const auto xx = rc.x;
    const auto yy = rc.y;
    const auto ww = originalSz? static_cast<x_real>( image->width() )  : size.width;
    const auto hh = originalSz? static_cast<x_real>( image->height() ) : size.height;

    canvas->drawImageRect(image,
                          {xx,yy,ww,hh},
                          SkSamplingOptions{} );
}




}

#endif // SKIA_HELPERS_H
