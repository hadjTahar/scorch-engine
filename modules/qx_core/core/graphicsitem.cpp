#include "graphicsitem.h"
#include "graphicsview.h"
#include "graphicsscene.h"


namespace Qx::prv
{

GraphicsItem::GraphicsItem(CoreItem *parent):
    CoreItem{ parent },
    transform{ this },
    rendering{ *this },
    m_graphicsScene{ nullptr },
    m_cameraZValue{0}
{

    // transform.setPosition( {0,0,0} );
    // transform.setScale(    {1,1,1} );
    // transform.setRotation( {0,0,0,1} );


    if( parent->isGraphicsItem() ){
        auto gParent = castItem<GraphicsItem>( parent );
        m_graphicsScene  = gParent->m_graphicsScene;
        dbg_assert_st( m_graphicsScene ) << "m_graphicsScene can't be null";
        m_graphicsScene->registerItem( this );
    }

    rendering.setVisible( true );
    rendering.setClipping( false);
    rendering.setCulling( true);
    rendering.setAntilalias( true);
    rendering.setLod( false);
    rendering.setIgnoreCamera( false );
}

GraphicsItem::~GraphicsItem()
{
    dbg_assert( m_graphicsScene ) << "m_graphicsScene can't be null";
    if( this == m_graphicsScene )
        return;
    m_graphicsScene->unregisterItem( this );
}

GraphicsItem *GraphicsItem::graphicsParentItem()
{
    return castItem<GraphicsItem>( parentItem() );
}

void GraphicsItem::updateRender()
{
    propagatePropertyStates( Qx::prv::PropertyStates::Render |
                            Qx::prv::PropertyStates::Transfom                            );
}

void GraphicsItem::updateProperties()
{
    const auto prntItm = parentItem();
    if( !prntItm->isWindowItem())
    {
        const auto gParent = castItem<GraphicsItem>(prntItm);
        const auto vsbl    = gParent->rendering.visible();
        if( rendering.visible() && !vsbl )
            rendering.setVisible( false );
    }

    const auto flag = prntItm->propertyStates();
    if( has_any( flag, PropertyStates::Transfom ) )
    {
        // dbg_print() << "case PropertyStates::Transfom";
        transform.m_dirtyLocal = true;
        transform.m_dirtyWorld = true;
    }
}

bool GraphicsItem::contains(const x_vector3 &pt) const
{
    /// ## Used for mouse event checks
    /// ## The checks must be done in (0,0,0) coords
    const auto sz = transform.size();
    if(pt.x < 0 || pt.y < 0/* || pt.z < 0*/ )
        return false;
    return pt.x <= sz.width && pt.y <= sz.height;
}

void GraphicsItem::updatePropertyStates(MetaItemType sceneTp)
{
    const auto itemTp  = meta_item_type();

    if( itemTp == MetaItemType::GraphicsItem2D )
        dbg_assert( sceneTp == MetaItemType::GraphicsScene2D ) <<
            "Mixing 2D and 3D in scene/item types, how did we get here";

    if( itemTp == MetaItemType::GraphicsItem3D )
        dbg_assert( sceneTp == MetaItemType::GraphicsScene3D ) <<
            "Mixing 2D and 3D in scene/item types, how did we get here";

    const auto tp = propertyStates();
    const auto needRender =
        has_any( tp,
                PropertyStates::Geometry |
                PropertyStates::Shape    |
                PropertyStates::Transfom |
                PropertyStates::Material
                );

    if( needRender )
        addPropertyStates( PropertyStates::Render );

}


void GraphicsItem::handleMouseEvent(const MouseEvent &event)
{
    mouseEvent( event );
}

void GraphicsItem::updateScreenSize(ScreenSize sz)
{
    m_screenSize = sz;
    screenSizeChanged();
    addPropertyStates( PropertyStates::Transfom | PropertyStates::Geometry );
    const auto &lst = childrenView();
    for ( auto &itm : lst){
        auto gItem = castItem<GraphicsItem>( itm.get() );
        gItem->updateScreenSize( sz );
    }
}


x_real GraphicsItem::cameraZValue() const
{
    return m_cameraZValue;
}

void GraphicsItem::setCameraZValue(x_real newCameraZValue)
{
    m_cameraZValue = newCameraZValue;
}

bool GraphicsItem::isSceneType( MetaItemType tp )
{
    return tp == MetaItemType::GraphicsScene2D || tp == MetaItemType::GraphicsScene3D;
}





}
