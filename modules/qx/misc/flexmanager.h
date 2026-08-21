#ifndef FLEXMANAGER_H
#define FLEXMANAGER_H

#include <items/flexlayout.h>
#include <yoga/Yoga.h>


namespace Qx::prv {

class FlexManager
{
public:

    static void processFlexNodes(Qx::FlexLayout *parentItem);

protected:
    static bool changed( Qx::prv::GraphicsItem2D  *parentItem);
    static bool childrenChanged( Qx::prv::GraphicsItem2D  *parentItem);


    static YGNodeRef createFLXChild(Qx::prv::GraphicsItem2D *glItem,
                                    YGNodeRef flxRoot,
                                    const x_count idx);

    static void setFlexPosition(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexMargin(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexPadding(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexBorder(YGNodeRef flxChild, FlexStyle *flxStyle );

    static void setFlexBasis(YGNodeRef flxChild, FlexStyle *flxStyle );


    static void setFlexWidth(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexHeight(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexMinWidth(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexMinHeight(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexMaxWidth(YGNodeRef flxChild, FlexStyle *flxStyle );
    static void setFlexMaxHeight(YGNodeRef flxChild, FlexStyle *flxStyle );


    static void applyFlex( YGNodeRef flxChild , prv::GraphicsItem2D *nd );

private:
    static void applyFlexPosition(YGNodeRef flxChild, const FlexSize &flxSz, FlexEdge flxEdge);
    static void applyFlexMargin(YGNodeRef flxChild,   const FlexSize &flxSz, FlexEdge flxEdge);
    static void applyFlexPadding(YGNodeRef flxChild,  const FlexSize &flxSz, FlexEdge flxEdge);
    static void applyFlexBorder(YGNodeRef flxChild,   const FlexSize &flxSz, FlexEdge flxEdge);
};

}

#endif // FLEXMANAGER_H
