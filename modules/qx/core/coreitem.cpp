#include "coreitem.h"

#include "graphicsscene.h"
#include "windowitem.h"

namespace Qx::prv
{

CoreItem *CoreItem::m_rootItem = nullptr;
std::vector<SmartItem>  CoreItem::m_addItems     = {};
std::vector<CoreItem*>  CoreItem::m_removedItems = {};

std::vector<SmartComp>  CoreItem::m_addComponents     = {};
std::vector<CoreComponent*>  CoreItem::m_removedComponents = {};


CoreItem::CoreItem(CoreItem *parent):
    m_parent{ parent },
    m_propertyStates{ PropertyStates::UpdateChildren},
    m_itemType{ ItemType::None}
{
    if( m_rootItem )
        dbg_assert( parent ) << "Only root can have a null parent";
    else
    {
        dbg_assert( !parent ) <<
            "Root can't be added with a parent (" << meta_type_name() << ")";
        m_rootItem = this;
    }

}

CoreItem::~CoreItem()
{
    m_components.clear();
    clearChildren();
    if( m_rootItem == this )
    {
        m_rootItem = nullptr;
        dbg_info_st() << "Groot! (goodbye root)";
        return;
    }
    if( !m_parent )
        return;
    m_parent->eraseChild( this );

}




void CoreItem::removeItem()
{
    m_removedItems.push_back( this );
}

// const CoreItem * const CoreItem::rootItem() const
// {
//     dbg_assert( m_rootItem ) << "Root item is null";
//     return m_rootItem;
// }

CoreItem *CoreItem::parentItem() const
{
    if( QX_DEF_ENABLE_META_DEBUGGING ){
        const x_string msg = "::parentItem reached root, root item should never be reach from ::parentItem()";
        dbg_assert( this != m_rootItem ) << msg;
        dbg_assert( m_parent != m_rootItem ) << msg;
        dbg_assert( m_parent ) << "Parent item is null";
    }
    return m_parent;
}


PropertyStates CoreItem::propertyStates() const
{
    return m_propertyStates;
}

void CoreItem::propertyChanged(PropertyStates newPropertyStates)
{
    addPropertyStates( newPropertyStates );
    m_propertyStates |= PropertyStates::UpdateChildren;
    propagatePropertyStates( newPropertyStates);
}

void CoreItem::propagatePropertyStates(PropertyStates newPropertyStates)
{
    addPropertyStates( PropertyStates::Render );
    if( isWindowItem() )
    {
        addPropertyStates( newPropertyStates );
        return;
    }

    const auto prntItm = parentItem();
    if( prntItm == m_rootItem )
        return;

    /// ## Parent already has the property, return
    const auto prntPropertyStates = prntItm->propertyStates();
    if( prntPropertyStates == newPropertyStates )
        return;
    prntItm->propertyChanged( newPropertyStates );
}

void CoreItem::addPropertyStates(PropertyStates newPropertyStates)
{
    m_propertyStates |= newPropertyStates;
}

void CoreItem::resetPropertyStates()
{
    m_propertyStates = PropertyStates::None;
}


void CoreItem::stepPendings()
{
    addPendingItems();
    removePendingItems();
}


void CoreItem::addPendingItems()
{
    for (auto& itm : m_addItems)
    {
        auto tmpParent = itm->m_parent;
        auto &lst = tmpParent->children();
        lst.push_back(std::move(itm));        
        tmpParent->lock( false );
    }

    for (auto& cmp : m_addComponents)
    {
        auto tmpParent = cmp->graphicsItem();
        tmpParent->m_components.push_back( std::move(cmp) );
    }

    m_addItems.clear();
    m_addComponents.clear();
}

void CoreItem::removePendingItems()
{
    for ( auto chldItm : m_removedItems)
    {
        chldItm->propagatePropertyStates( PropertyStates::Transfom );
        auto tmpParent = chldItm->m_parent;
        auto &lst = tmpParent->children();
        auto it = std::find_if(lst.begin(),
                               lst.end(),
                               [chldItm](const SmartItem& itm)
                               {
                                   return itm.get() == chldItm;
                               });
        const auto found = (it != lst.end());
        dbg_assert_st( found ) << "Couldn't find child in parents chidlren";

        /// ## 'tmpParent->lock( false )' should be after
        /// ## it->reset( chldItm );
        /// ## but the destructor of chldItm will call (parent->children())
        /// ## and assert will fail
        tmpParent->lock( false );
        it->reset();
    }


    for (auto rmCmp : m_removedComponents)
    {
        auto tmpParent = rmCmp->graphicsItem();
        auto &lst = tmpParent->m_components;
        auto it = std::find_if(lst.begin(),
                               lst.end(),
                               [rmCmp](const SmartComp& cmp)
                               {
                                   return cmp.get() == rmCmp;
                               });


        const auto found = (it != lst.end());
        dbg_assert_st( found ) << "Couldn't find component in parents components";
        it->reset();
    }


    m_removedItems.clear();
    m_removedComponents.clear();

}


void CoreItem::updateItem(MetaItemType sceneType)
{
    MetaObject::check_is_alive( this );
    updatePropertyStates(sceneType);
    const auto propertyTp = m_propertyStates;
    const auto updateChildren = has_any( propertyTp, PropertyStates::UpdateChildren );


    addPropertyStates( PropertyStates::Render );
    if( !updateChildren )
        return;

    const auto &lst = childrenView();
    for ( auto &itm : lst)
    {
        auto chldItm = castItem<GraphicsItem>( itm.get() );
        chldItm->updateProperties();
        itm->updateItem( sceneType );
        itm->addPropertyStates( PropertyStates::Render );
    }
    // m_propertyStates = PropertyStates::Render;
}


void CoreItem::renderItem(Canvas *cnvs)
{
    MetaObject::check_is_alive( this );
    render( cnvs );
}

 void CoreItem::renderItem()
{
    MetaObject::check_is_alive( this );
    updateModel();
}


x_count CoreItem::hierarchyIndex() const
{
    if( isWindowItem() )
        return 1;

    else if( this == m_rootItem )
        return 0;

    auto prnt = parentItem();
    x_count ret = 0;

    while ( prnt != m_rootItem )
    {
        if( prnt->isWindowItem() )
        {
            ++ret;
            break;
        }

        ++ret;
        prnt = prnt->parentItem();
    }

    return ret;
}

void CoreItem::clearChildren()
{
    /// ##TODO: Should I call m_components.clear();
    /// ## in "~CoreItem" for "::~CoreComponent"
    /// ## "CoreItem::m_parent" becomes null
    ///
    auto &lst = children();
    /// ## Set the parents to null
    /// ## so children won't try to remove themselves
    /// ## from the parents, in the destructors
    for ( auto &chld : lst)
        chld->m_parent = nullptr;

    lst.clear();
    lock( false );
}


void CoreItem::eraseChild(CoreItem *chld)
{
    /// ## chld is deleted at this point, don't use it
    /// ## This should be only called from the child destructor
    /// like m_parent->eraseChild( this );
    ///
    auto &lst = children();
    auto it = std::find_if(lst.begin(),
                           lst.end(),
                           [chld](const SmartItem& itm)
                           {
                               return !itm.get() || itm.get() == chld;
                           });


    dbg_assert( it != lst.end() ) << "Can't find item or null item in parent";

    if( it->get() )
        dbg_assert( it != lst.end()) << "Can't find item in parent";
    else
        /// ## This was destructed from "::removePendingItems"
        /// ## it won't find a valid child  pointer in m_children
        /// ## so we assert it's a null child
        ///
        dbg_assert( !it->get() ) << "Can't find item (null) in parent";

    /// ## This is called from the child destructor
    /// ## We release it, so that ::erase
    /// ## won't cause recursive calls for destructor
    it->release();
    lst.erase( it );
    lock( false );
}


std::vector<SmartItem> &CoreItem::children()
{
    dbg_assert( !locked() ) << "Can't access a locked children list";
    lock( true );
    return m_children;
}

bool CoreItem::isWindowItem() const
{
    return m_itemType == ItemType::Window;
    // /// ## Bad design, this assumes (Root(APP) -> Window )
    // /// ## hierarchy is always true
    // return (m_parent == m_rootItem);
}

bool CoreItem::isSceneItem2D() const
{
    return m_itemType == ItemType::GraphicsScene2D;
}

bool CoreItem::isSceneItem3D() const
{
    return m_itemType == ItemType::GraphicsScene3D;
}

bool CoreItem::isSceneItem() const
{
    // return parentItem()->isWindowItem();
    return isSceneItem2D() || isSceneItem3D();
}

bool CoreItem::isGraphicsItem2D() const
{
    return m_itemType == ItemType::GraphicsItem2D;
}

bool CoreItem::isGraphicsItem3D() const
{
    return m_itemType == ItemType::GraphicsItem3D;
}

bool CoreItem::isGraphicsItem() const
{
    const auto gtp = static_cast<int>( ItemType::GraphicsItem2D );
    const auto itp = static_cast<int>( m_itemType );

    return itp >= gtp;
    // return isGraphicsItem2D() || isGraphicsItem3D() || isSceneItem();
}

void CoreItem::meta_check_hierarchy()
{
    if( !QX_DEF_ENABLE_META_DEBUGGING )
        return;
    const auto &lst = childrenView();
    for ( auto &itm : lst)
    {
        const auto match = static_cast<bool>(itm->m_parent->meta_child_type() &
                                             itm->meta_item_type());
        dbg_assert_st( match ) <<
            "Item types mismatch, you can't add " <<
            itm->meta_type_name() << " to " <<
            itm->m_parent->meta_type_name();
    }
}








}
