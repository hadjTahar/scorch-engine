#include "flexmanager.h"


namespace Qx::prv {

void FlexManager::processFlexNodes(FlexLayout *parentItem)
{
    /// bool chg = changed( parentItem ) || childrenChanged( parentItem );
    bool chg = changed( parentItem );
    if( !chg )
        return;

    /// ## Create flex children from "FlexStyle"
    /// ## And calculate the layout
    /// ## -----------------------------------------------------------------
    /// ## -----------------------------------------------------------------
    ///

    YGNodeRef flxRoot = createFLXChild( parentItem, nullptr, 0 );
    const auto sz     = parentItem->transform.size();

    std::map<YGNodeRef,prv::GraphicsItem2D* > flxItems;

    const auto &chldNodes = parentItem->childrenView();
    for ( auto &nd : chldNodes)
    {
        auto g2dNd = prv::CoreItem::castItem<prv::GraphicsItem2D,
                              prv::MetaItemType::GraphicsItem2D>( nd.get() );
        const auto idx = flxItems.size();
        const auto flxChld = createFLXChild( g2dNd, flxRoot, idx );
        flxItems[ flxChld ] = g2dNd;
    }

    YGNodeCalculateLayout(flxRoot,
                          sz.width,
                          sz.height,
                          static_cast<YGDirection>( parentItem->flexStyle()->layoutDirection )
                          );



    /// ## Apply flex results to nodes
    /// ## -----------------------------------------------------------------
    /// ## -----------------------------------------------------------------
    ///
    /// ## X DONT applyFlex( flxRoot, parentItem );
    /// ## applyFlex( flxRoot, parentItem );
    for (auto& [flxChld, g2dNd] : flxItems)
        applyFlex( flxChld, g2dNd );

    /// ## Clean
    /// ## -----------------------------------------------------------------
    /// ## -----------------------------------------------------------------
    ///
    YGNodeFreeRecursive( flxRoot );
}

bool FlexManager::changed(prv::GraphicsItem2D *parentItem)
{
    const auto tp = parentItem->propertyStates();
    return has_any( tp, PropertyStates::Geometry | PropertyStates::Transfom );
    // return parentItem->propertiesChanged();
}

bool FlexManager::childrenChanged(prv::GraphicsItem2D *parentItem)
{
    dbg_unused( parentItem );
    return true;
    // bool chg = false;
    // const auto chldNodes = parentItem->constChildrenNodes();
    // for ( auto &nd : *chldNodes)
    // {
    //     chg = chg || nd->propertiesChanged();
    //     if( chg )
    //         break;
    // }

    // return chg;
}


YGNodeRef FlexManager::createFLXChild(prv::GraphicsItem2D *glItem,
                                      YGNodeRef flxRoot,
                                      const x_count idx)
{

    const auto flxStyle = glItem->flexStyle();
    YGNodeRef flxChild = YGNodeNew();

    YGNodeStyleSetAlignContent(flxChild, static_cast<YGAlign>( flxStyle->alignContent ));
    YGNodeStyleSetAlignSelf(flxChild, static_cast<YGAlign>( flxStyle->alignSelf ));
    YGNodeStyleSetAlignItems(flxChild, static_cast<YGAlign>( flxStyle->alignItems ));



    if( flxStyle->flex >= 0 )
        YGNodeStyleSetFlex(flxChild, flxStyle->flex );

    if( flxStyle->aspectRatio >= 0 )
        YGNodeStyleSetAspectRatio(flxChild, flxStyle->aspectRatio );


    if( !glItem->rendering.visible() )
        YGNodeStyleSetDisplay(flxChild, static_cast<YGDisplay>( FlexDisplay::None ));
    else
        YGNodeStyleSetDisplay(flxChild, static_cast<YGDisplay>( flxStyle->display ));


    setFlexBasis( flxChild, flxStyle );
    YGNodeStyleSetFlexGrow( flxChild, flxStyle->flexGrow );
    YGNodeStyleSetFlexShrink( flxChild, flxStyle->flexShrink );
    YGNodeStyleSetFlexDirection(flxChild, static_cast<YGFlexDirection>( flxStyle->flexDirection ));
    YGNodeStyleSetFlexWrap(flxChild, static_cast<YGWrap>( flxStyle->flexWrap ));
    YGNodeStyleSetGap(flxChild,
                      static_cast<YGGutter>( flxStyle->gap.gutter ),
                      100 * flxStyle->gap.value );

    YGNodeStyleSetJustifyContent(flxChild, static_cast<YGJustify>( flxStyle->justifyContent ));
    YGNodeStyleSetDirection(flxChild, static_cast<YGDirection>( flxStyle->layoutDirection ));


    setFlexPosition( flxChild, flxStyle );
    setFlexMargin( flxChild, flxStyle );
    setFlexPadding( flxChild, flxStyle );
    setFlexBorder( flxChild, flxStyle );
    YGNodeStyleSetPositionType( flxChild, static_cast<YGPositionType>( flxStyle->positionType ) );

    YGNodeStyleSetOverflow( flxChild, static_cast<YGOverflow>( flxStyle->overflow ) );
    /// ## If it's a parent node, use its size, not the flex size
    if( !flxRoot )
    {
        const auto ndSz = glItem->transform.size();
        YGNodeStyleSetWidth(flxChild, ndSz.width );
        YGNodeStyleSetHeight(flxChild, ndSz.height );

        // YGNodeStyleSetMinWidth(flxChild, ndSz.x );
        // YGNodeStyleSetMinHeight(flxChild, ndSz.y );

        // YGNodeStyleSetMaxWidth(flxChild, ndSz.x );
        // YGNodeStyleSetMaxHeight(flxChild, ndSz.y );
    }
    else
    {
        setFlexWidth( flxChild, flxStyle );
        setFlexHeight( flxChild, flxStyle );
        setFlexMinWidth( flxChild, flxStyle );
        setFlexMinHeight( flxChild, flxStyle );
        setFlexMaxWidth( flxChild, flxStyle );
        setFlexMaxHeight( flxChild, flxStyle );
    }


    if( flxRoot )
        YGNodeInsertChild(flxRoot, flxChild, idx );
    return flxChild;
}

void FlexManager::setFlexPosition(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    applyFlexPosition( flxChild, flxStyle->position.left,       Qx::FlexEdge::Left );
    applyFlexPosition( flxChild, flxStyle->position.top,        Qx::FlexEdge::Top );
    applyFlexPosition( flxChild, flxStyle->position.right,      Qx::FlexEdge::Right );
    applyFlexPosition( flxChild, flxStyle->position.bottom,     Qx::FlexEdge::Bottom );
    applyFlexPosition( flxChild, flxStyle->position.start,      Qx::FlexEdge::Start );
    applyFlexPosition( flxChild, flxStyle->position.end,        Qx::FlexEdge::End );
    applyFlexPosition( flxChild, flxStyle->position.horizontal, Qx::FlexEdge::Horizontal );
    applyFlexPosition( flxChild, flxStyle->position.vertical,   Qx::FlexEdge::Vertical );
    applyFlexPosition( flxChild, flxStyle->position.all,        Qx::FlexEdge::All );

}

void FlexManager::setFlexMargin(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    applyFlexMargin( flxChild, flxStyle->margin.left,       Qx::FlexEdge::Left );
    applyFlexMargin( flxChild, flxStyle->margin.top,        Qx::FlexEdge::Top );
    applyFlexMargin( flxChild, flxStyle->margin.right,      Qx::FlexEdge::Right );
    applyFlexMargin( flxChild, flxStyle->margin.bottom,     Qx::FlexEdge::Bottom );
    applyFlexMargin( flxChild, flxStyle->margin.start,      Qx::FlexEdge::Start );
    applyFlexMargin( flxChild, flxStyle->margin.end,        Qx::FlexEdge::End );
    applyFlexMargin( flxChild, flxStyle->margin.horizontal, Qx::FlexEdge::Horizontal );
    applyFlexMargin( flxChild, flxStyle->margin.vertical,   Qx::FlexEdge::Vertical );
    applyFlexMargin( flxChild, flxStyle->margin.all,        Qx::FlexEdge::All );

}

void FlexManager::setFlexPadding(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    applyFlexPadding( flxChild, flxStyle->padding.left,       Qx::FlexEdge::Left );
    applyFlexPadding( flxChild, flxStyle->padding.top,        Qx::FlexEdge::Top );
    applyFlexPadding( flxChild, flxStyle->padding.right,      Qx::FlexEdge::Right );
    applyFlexPadding( flxChild, flxStyle->padding.bottom,     Qx::FlexEdge::Bottom );
    applyFlexPadding( flxChild, flxStyle->padding.start,      Qx::FlexEdge::Start );
    applyFlexPadding( flxChild, flxStyle->padding.end,        Qx::FlexEdge::End );
    applyFlexPadding( flxChild, flxStyle->padding.horizontal, Qx::FlexEdge::Horizontal );
    applyFlexPadding( flxChild, flxStyle->padding.vertical,   Qx::FlexEdge::Vertical );
    applyFlexPadding( flxChild, flxStyle->padding.all,        Qx::FlexEdge::All );

}

void FlexManager::setFlexBorder(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    applyFlexBorder( flxChild, flxStyle->border.left,       Qx::FlexEdge::Left );
    applyFlexBorder( flxChild, flxStyle->border.top,        Qx::FlexEdge::Top );
    applyFlexBorder( flxChild, flxStyle->border.right,      Qx::FlexEdge::Right );
    applyFlexBorder( flxChild, flxStyle->border.bottom,     Qx::FlexEdge::Bottom );
    applyFlexBorder( flxChild, flxStyle->border.start,      Qx::FlexEdge::Start );
    applyFlexBorder( flxChild, flxStyle->border.end,        Qx::FlexEdge::End );
    applyFlexBorder( flxChild, flxStyle->border.horizontal, Qx::FlexEdge::Horizontal );
    applyFlexBorder( flxChild, flxStyle->border.vertical,   Qx::FlexEdge::Vertical );
    applyFlexBorder( flxChild, flxStyle->border.all,        Qx::FlexEdge::All );

}

void FlexManager::setFlexBasis(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->flexBasis;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetFlexBasis( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetFlexBasisPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        YGNodeStyleSetFlexBasisAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetFlexBasisMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetFlexBasisFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetFlexBasisStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::setFlexWidth(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->width;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetWidth( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetWidthPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        YGNodeStyleSetWidthAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetWidthMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetWidthFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetWidthStretch( flxChild );
        break;

    default:
        break;
    }

}

void FlexManager::setFlexHeight(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->height;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetHeight( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetHeightPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        YGNodeStyleSetHeightAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetHeightMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetHeightFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetHeightStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::setFlexMinWidth(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->minWidth;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetMinWidth( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetMinWidthPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        dbg_warning() << "Flex Unit auto can't be set for min width size";
        // YGNodeStyleSetMinWidthAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetMinWidthMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetMinWidthFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetMinWidthStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::setFlexMinHeight(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->minHeight;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetMinHeight( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetMinHeightPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        dbg_warning() << "Flex Unit auto can't be set for min Height size";
        // YGNodeStyleSetMinHeightAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetMinHeightMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetMinHeightFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetMinHeightStretch( flxChild );
        break;
    default:
        break;
    }
}

void FlexManager::setFlexMaxWidth(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->maxWidth;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetMaxWidth( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetMaxWidthPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        dbg_warning() << "Flex Unit auto can't be set for max width size";
        // YGNodeStyleSetMaxWidthAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetMaxWidthMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetMaxWidthFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetMaxWidthStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::setFlexMaxHeight(YGNodeRef flxChild, FlexStyle *flxStyle)
{
    const auto sz     = flxStyle->maxHeight;
    const auto szVal  = sz.value;
    const auto szUnt  = sz.flexUnit;

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetMaxHeight( flxChild, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetMaxHeightPercent( flxChild, 100 * szVal );
        break;
    case FlexUnit::Auto:
        dbg_warning() << "Flex Unit auto can't be set for max height size";
        // YGNodeStyleSetMaxHeightAuto( flxChild );
        break;
    case FlexUnit::MaxContent:
        YGNodeStyleSetMaxHeightMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        YGNodeStyleSetMaxHeightFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        YGNodeStyleSetMaxHeightStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::applyFlex(YGNodeRef flxChild, prv::GraphicsItem2D *nd)
{
    const auto xx = YGNodeLayoutGetLeft( flxChild );
    const auto yy = YGNodeLayoutGetTop( flxChild );

    const auto ww = YGNodeLayoutGetWidth( flxChild );
    const auto hh = YGNodeLayoutGetHeight( flxChild );


    const auto oldPos = nd->transform.position();
    const auto oldSz  = nd->transform.size();

    nd->transform.setPosition( {xx, yy, oldPos.z   } );
    nd->transform.setSize(     {ww, hh, oldSz.depth} );
}


void FlexManager::applyFlexPosition(YGNodeRef flxChild,
                                    const FlexSize &flxSz,
                                    FlexEdge flxEdge
                                    )
{
    const auto szVal  = flxSz.value;
    const auto szUnt  = flxSz.flexUnit;
    const auto ygEdge = static_cast<YGEdge>( flxEdge );

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetPosition(flxChild, ygEdge, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetPositionPercent( flxChild, ygEdge, 100 * szVal );
        break;
    case FlexUnit::Auto:
        YGNodeStyleSetPositionAuto( flxChild, ygEdge );
        break;
    case FlexUnit::MaxContent:
        dbg_warning() << "Flex Unit MaxContent can't be set for position";
        // YGNodeStyleSetPositionMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        dbg_warning() << "Flex Unit FitContent can't be set for position";
        // YGNodeStyleSetPositionFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        dbg_warning() << "Flex Unit Stretch can't be set for position";
        // YGNodeStyleSetPositionStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::applyFlexMargin(YGNodeRef flxChild,
                                  const FlexSize &flxSz,
                                  FlexEdge flxEdge)
{
    const auto szVal  = flxSz.value;
    const auto szUnt  = flxSz.flexUnit;
    const auto ygEdge = static_cast<YGEdge>( flxEdge );

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetMargin(flxChild, ygEdge, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetMarginPercent( flxChild, ygEdge, 100 * szVal );
        break;
    case FlexUnit::Auto:
        YGNodeStyleSetMarginAuto( flxChild, ygEdge );
        break;
    case FlexUnit::MaxContent:
        dbg_warning() << "Flex Unit MaxContent can't be set for margin";
        // YGNodeStyleSetMarginMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        dbg_warning() << "Flex Unit FitContent can't be set for margin";
        // YGNodeStyleSetMarginFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        dbg_warning() << "Flex Unit Stretch can't be set for margin";
        // YGNodeStyleSetMarginStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::applyFlexPadding(YGNodeRef flxChild,
                                   const FlexSize &flxSz,
                                   FlexEdge flxEdge)
{
    const auto szVal  = flxSz.value;
    const auto szUnt  = flxSz.flexUnit;
    const auto ygEdge = static_cast<YGEdge>( flxEdge );

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetPadding(flxChild, ygEdge, szVal );
        break;
    case FlexUnit::Percent:
        YGNodeStyleSetPaddingPercent( flxChild, ygEdge, 100 * szVal );
        break;
    case FlexUnit::Auto:
        dbg_warning() << "Flex Unit Auto can't be set for padding";
        // YGNodeStyleSetPaddingAuto( flxChild, ygEdge );
        break;
    case FlexUnit::MaxContent:
        dbg_warning() << "Flex Unit MaxContent can't be set for padding";
        // YGNodeStyleSetPaddingMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        dbg_warning() << "Flex Unit FitContent can't be set for padding";
        // YGNodeStyleSetPaddingFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        dbg_warning() << "Flex Unit Stretch can't be set for padding";
        // YGNodeStyleSetPaddingStretch( flxChild );
        break;

    default:
        break;
    }
}

void FlexManager::applyFlexBorder(YGNodeRef flxChild,
                                  const FlexSize &flxSz,
                                  FlexEdge flxEdge)
{
    const auto szVal  = flxSz.value;
    const auto szUnt  = flxSz.flexUnit;
    const auto ygEdge = static_cast<YGEdge>( flxEdge );

    switch ( szUnt ) {
    case FlexUnit::Undefined:
        break;
    case FlexUnit::Pixels:
        YGNodeStyleSetBorder(flxChild, ygEdge, szVal );
        break;
    case FlexUnit::Percent:
        dbg_warning() << "Flex Unit Percent can't be set for border";
        // YGNodeStyleSetBorderPercent( flxChild, ygEdge, 100 * szVal );
        break;
    case FlexUnit::Auto:
        dbg_warning() << "Flex Unit Auto can't be set for border";
        // YGNodeStyleSetBorderAuto( flxChild, ygEdge );
        break;
    case FlexUnit::MaxContent:
        dbg_warning() << "Flex Unit MaxContent can't be set for border";
        // YGNodeStyleSetBorderMaxContent( flxChild );
        break;
    case FlexUnit::FitContent:
        dbg_warning() << "Flex Unit FitContent can't be set for border";
        // YGNodeStyleSetBorderFitContent( flxChild );
        break;
    case FlexUnit::Stretch:
        dbg_warning() << "Flex Unit Stretch can't be set for border";
        // YGNodeStyleSetBorderStretch( flxChild );
        break;

    default:
        break;
    }
}

}
