#ifndef FLEXSTYLE_H
#define FLEXSTYLE_H

#include <yoga/YGEnums.h>
#include <core/metaobject.h>
#include "defs.h"


namespace Qx {

enum class FlexAlign {
    Auto            = YGAlignAuto,
    FlexStart       = YGAlignFlexStart,
    Center          = YGAlignCenter,
    FlexEnd         = YGAlignFlexEnd,
    Stretch         = YGAlignStretch,
    Baseline        = YGAlignBaseline,
    SpaceBetween    = YGAlignSpaceBetween,
    SpaceAround     = YGAlignSpaceAround,
    SpaceEvenly     = YGAlignSpaceEvenly
};

enum class FlexBoxSizing {
    BorderBox  = YGBoxSizingBorderBox,
    ContentBox = YGBoxSizingContentBox
};

enum class FlexDimension {
    Width  = YGDimensionWidth,
    Height = YGDimensionHeight
};

enum class LayoutDirection {
    Inherit = YGDirectionInherit,
    LTR     = YGDirectionLTR,
    RTL     = YGDirectionRTL
};

enum class FlexDisplay {
    Flex     = YGDisplayFlex,
    None     = YGDisplayNone,
    Contents = YGDisplayContents,
    Ignore   /// ## Custom for top level nodes like (dialogs) to be ignored
};

enum class FlexEdge {
    Left        = YGEdgeLeft,
    Top         = YGEdgeTop,
    Right       = YGEdgeRight,
    Bottom      = YGEdgeBottom,
    Start       = YGEdgeStart,
    End         = YGEdgeEnd,
    Horizontal  = YGEdgeHorizontal,
    Vertical    = YGEdgeVertical,
    All         = YGEdgeAll
};

enum class FlexErrata {
    None                                         = YGErrataNone,
    StretchFlexBasis                             = YGErrataStretchFlexBasis,
    AbsolutePositionWithoutInsetsExcludesPadding = YGErrataAbsolutePositionWithoutInsetsExcludesPadding,
    AbsolutePercentAgainstInnerSize              = YGErrataAbsolutePercentAgainstInnerSize,
    All                                          = YGErrataAll,
    Classic                                      = YGErrataClassic
};
// You'd still need to define flag operators separately for FlexErrata if required.

enum class FlexExperimentalFeature {
    WebFlexBasis = YGExperimentalFeatureWebFlexBasis
};

enum class FlexDirection {
    Column         = YGFlexDirectionColumn,
    ColumnReverse  = YGFlexDirectionColumnReverse,
    Row            = YGFlexDirectionRow,
    RowReverse     = YGFlexDirectionRowReverse
};

enum class FlexGutter {
    Column = YGGutterColumn,
    Row    = YGGutterRow,
    All    = YGGutterAll
};

enum class FlexJustify {
    FlexStart       = YGJustifyFlexStart,
    Center          = YGJustifyCenter,
    FlexEnd         = YGJustifyFlexEnd,
    SpaceBetween    = YGJustifySpaceBetween,
    SpaceAround     = YGJustifySpaceAround,
    SpaceEvenly     = YGJustifySpaceEvenly
};

enum class FlexLogLevel {
    Error       = YGLogLevelError,
    Warn        = YGLogLevelWarn,
    Info        = YGLogLevelInfo,
    Debug       = YGLogLevelDebug,
    Verbose     = YGLogLevelVerbose,
    Fatal       = YGLogLevelFatal
};

enum class FlexMeasureMode {
    Undefined   = YGMeasureModeUndefined,
    Exactly     = YGMeasureModeExactly,
    AtMost      = YGMeasureModeAtMost
};

enum class FlexNodeType {
    Default = YGNodeTypeDefault,
    Text    = YGNodeTypeText
};

enum class FlexOverflow {
    Visible = YGOverflowVisible,
    Hidden  = YGOverflowHidden,
    Scroll  = YGOverflowScroll
};

enum class FlexPositionType {
    Static    = YGPositionTypeStatic,
    Relative  = YGPositionTypeRelative,
    Absolute  = YGPositionTypeAbsolute
};

enum class FlexUnit {
    Undefined   = YGUnitUndefined,
    Pixels      = YGUnitPoint,
    Percent     = YGUnitPercent,
    Auto        = YGUnitAuto,
    MaxContent  = YGUnitMaxContent,
    FitContent  = YGUnitFitContent,
    Stretch     = YGUnitStretch
};

enum class FlexWrap {
    NoWrap = YGWrapNoWrap,
    Wrap = YGWrapWrap,
    WrapReverse = YGWrapWrapReverse
};

/// ## ----------------------------------------------------------------------
/// ##
///

struct FlexGap
{
    x_real   value;
    FlexGutter  gutter{FlexGutter::All};

    /// ## Helpers
    /// ## To reduce { size, enum}

    static constexpr inline FlexGap column(x_real vl){ return {vl, Qx::FlexGutter::Column};}
    static constexpr inline FlexGap row(x_real vl)   { return {vl, Qx::FlexGutter::Row};}
    static constexpr inline FlexGap all(x_real vl)   { return {vl, Qx::FlexGutter::All};}

};

struct FlexSize
{
    x_real  value = { 0 };
    FlexUnit   flexUnit{FlexUnit::Undefined};

    /// ## Helpers
    /// ## To reduce { size, enum}

    static constexpr inline FlexSize undefined()              { return {0,       Qx::FlexUnit::Undefined};}
    static constexpr inline FlexSize pixels( x_real vl )      { return {vl,      Qx::FlexUnit::Pixels};}
    static constexpr inline FlexSize percent( x_real percent) { return {percent, Qx::FlexUnit::Percent};}
    static constexpr inline FlexSize autoFlex()               { return {0,       Qx::FlexUnit::Auto};}
    static constexpr inline FlexSize maxContent()             { return {0,       Qx::FlexUnit::MaxContent};}
    static constexpr inline FlexSize fitContent()             { return {0,       Qx::FlexUnit::FitContent};}
    static constexpr inline FlexSize stretch()                { return {0,       Qx::FlexUnit::Stretch};}
};


struct FlexEdgeSize
{

    FlexSize left;
    FlexSize top;
    FlexSize right;
    FlexSize bottom;
    FlexSize start;
    FlexSize end;
    FlexSize horizontal;
    FlexSize vertical;
    FlexSize all;
};


class FlexStyle : public prv::MetaObject
{

    QX_META_OBJECT( "FlexStyle",
                   prv::MetaItemType::NA,
                   prv::MetaItemType::NA )
public:

    // ---- Flex properties ----
    LayoutDirection layoutDirection;  // LTR, RTR.
    FlexDirection flexDirection;      // Row, Column, etc.
    FlexJustify justifyContent;       // FlexStart, Center, SpaceBetween...
    FlexAlign alignItems;             // How children align on cross axis
    FlexAlign alignSelf;              // For this item inside its parent
    FlexAlign alignContent;           // Multi-line alignment
    FlexWrap flexWrap;                // NoWrap, Wrap, WrapReverse
    FlexDisplay display;              // Flex or None
    FlexOverflow overflow;            // Visible, Hidden, Scroll
    FlexPositionType positionType;    // Static, Relative, Absolute

    // ---- Flex sizing ----
    x_real flex;                       // To fill parent: flexGrow=1, flexShrink=1, flexBasis=0
    x_real flexGrow;                   // Grow ratio
    x_real flexShrink;                 // Shrink ratio
    x_real aspectRatio;                // Aspect Ratio

    FlexSize flexBasis;               // Default size before growing/shrinking
    // ---- Fixed sizing ----
    FlexSize  width;
    FlexSize  height;
    FlexSize  minWidth;
    FlexSize  minHeight;
    FlexSize  maxWidth;
    FlexSize  maxHeight;

    // ---- Edges (margins, paddings, positions) ----
    FlexEdgeSize position = {};
    FlexEdgeSize margin   = {};
    FlexEdgeSize padding  = {};
    FlexEdgeSize border   = {};
    FlexGap      gap;



    /// ------------------------------------------------------
    ///
     inline FlexStyle():
        layoutDirection{ LayoutDirection::LTR },
        flexDirection{ FlexDirection::Column },
        justifyContent{ FlexJustify::FlexStart },
        alignItems{ FlexAlign::Stretch },
        alignSelf{ FlexAlign::Auto },
        alignContent{ FlexAlign::FlexStart },
        positionType{ FlexPositionType::Relative },
        flexWrap{ FlexWrap::NoWrap },
        display{ FlexDisplay::Flex },
        overflow{ FlexOverflow::Visible },
        flex{ -1.0f },
        flexGrow{ 1.0f },
        flexShrink{ 1.0f },
        flexBasis{ 0 },
        aspectRatio{ -1.0f },
        width{ 0, Qx::FlexUnit::Undefined },
        height{ 0, Qx::FlexUnit::Undefined },
        minWidth{ 0, Qx::FlexUnit::Undefined },
        minHeight{ 0, Qx::FlexUnit::Undefined },
        maxWidth{ 0, Qx::FlexUnit::Undefined },
        maxHeight{ 0, Qx::FlexUnit::Undefined },
        gap{ 0.f, FlexGutter::All}
    {
        defaults();
    }

    /// ## Helpers
    /// ------------------------------------------------------
    ///

    inline void defaults()
    {
        layoutDirection = { LayoutDirection::LTR };
        flexDirection = { FlexDirection::Column };
        justifyContent = { FlexJustify::FlexStart };
        alignItems = { FlexAlign::Stretch };
        alignSelf = { FlexAlign::Auto };
        alignContent = { FlexAlign::FlexStart };
        positionType = { FlexPositionType::Relative };
        flexWrap = { FlexWrap::NoWrap };
        display = { FlexDisplay::Flex };
        overflow = { FlexOverflow::Visible };
        flex = { -1.0f };
        flexGrow = { 1.0f };
        flexShrink = { 1.0f };
        flexBasis = { 0 };
        aspectRatio = { -1.0f };
        width = { 0, Qx::FlexUnit::Undefined };
        height = { 0, Qx::FlexUnit::Undefined };
        minWidth = { 0, Qx::FlexUnit::Undefined };
        minHeight = { 0, Qx::FlexUnit::Undefined };
        maxWidth = { 0, Qx::FlexUnit::Undefined };
        maxHeight = { 0, Qx::FlexUnit::Undefined };
        gap = { 0.f, FlexGutter::All};
    }

    inline void centerItems()
    {
        // Set parent properties: JustifyContent: Center and AlignItems: Center.
        justifyContent = FlexJustify::Center;
        alignItems = FlexAlign::Center;
    }

    inline void fillParent()
    {
        width  = FlexSize::percent( 1 );
        height = FlexSize::percent( 1 );
    }

    inline void containerLayout()
    {
        defaults();
    }

    inline void gridLayout()
    {
        defaults();
        flex = 1;
        flexWrap = Qx::FlexWrap::Wrap;
        flexDirection = Qx::FlexDirection::Row;
        alignSelf = Qx::FlexAlign::Center;
        alignItems = Qx::FlexAlign::Center;
        alignContent = Qx::FlexAlign::Center;
        justifyContent = Qx::FlexJustify::Center;
    }

    inline void tilesLayout( Qx::x_real borders )
    {
        defaults();
        flex = 1;
        flexWrap = Qx::FlexWrap::Wrap;
        flexDirection = Qx::FlexDirection::Row;
        alignSelf = Qx::FlexAlign::Auto;
        alignItems = Qx::FlexAlign::FlexStart;
        alignContent = Qx::FlexAlign::FlexStart;
        justifyContent = Qx::FlexJustify::FlexStart;
        border.all = { borders, Qx::FlexUnit::Pixels };
    }

    inline void  spacerNode()
    {
        defaults();
        width  = Qx::FlexSize::percent( 1 );
        height = Qx::FlexSize::percent( 1 );
    }


    inline void  hBarNode()
    {
        defaults();
        height = Qx::FlexSize::percent( 1 );
        aspectRatio = 1;

        flexGrow = 0;
        flexShrink = 0;
        flexBasis = Qx::FlexSize::autoFlex();
    }

    inline void  vBarNode()
    {
        defaults();
        width = Qx::FlexSize::percent( 1 );
        aspectRatio = 1;

        flexGrow = 0;
        flexShrink = 0;
        flexBasis = Qx::FlexSize::autoFlex();
    }
};


}


#endif // FLEXSTYLE_H
