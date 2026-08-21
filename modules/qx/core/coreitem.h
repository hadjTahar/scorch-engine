#ifndef COREITEM_H
#define COREITEM_H


#include "metaobject.h"

#include <misc/flags.h>
#include <rendering/canvas.h>
#include <rendering/graphicsmodel.h>
#include <components/corecomponent.h>
#include <bitset>


namespace Qx
{
class CameraController;
}
namespace Qx::prv
{

using SmartComp = std::unique_ptr<CoreComponent>;

class RootBaseItem;
class GraphicsScene;
class GraphicsView;
class WindowItem;

class CoreItem;
using SmartItem = std::unique_ptr<CoreItem>;

class CoreItem : public MetaObject
{

    friend class Application;
    friend class GraphicsScene;
    friend class GraphicsScene2D;
    friend class GraphicsScene3D;
    friend class GraphicsItem;
    friend class CoreComponent;
    friend class WindowItem;
    friend class CameraController;

public:


    CoreItem( CoreItem *parent);
    virtual ~CoreItem();
    /// ## API
    /// ## This is a misnomer
    inline const std::vector<SmartItem>&childrenView() const
    {
        dbg_assert(!locked())<<"Can't access a locked children list";
        return m_children;
    }
    template<typename Type> Type *addItem()
    {
        return makeItem<Type>( this );
    }
    void removeItem();


    CoreItem *parentItem() const;

    PropertyStates propertyStates() const;
    void propertyChanged(PropertyStates newPropertyStates) override;
    void propagatePropertyStates(PropertyStates newPropertyStates);
    void addPropertyStates(PropertyStates newPropertyStates);
    void resetPropertyStates();

    template<typename Type> static std::unique_ptr<Type> addRootItem()
    {
        dbg_assert_st( !m_rootItem ) << "Can't a add root, it's already defined";
        auto ret = CoreItem::makeUniqueItem<Type,true>();
        Type::mustBeRootBased();
        return ret;
    }

    static inline constexpr auto meta_is_graphics_item_based( MetaItemType itmType)
    {
        /// ## This only works if meta tracking is enabled
        return has_any( itmType, MetaItemType::GraphicsItem2D    |
                                    MetaItemType::GraphicsItem3D |
                                    MetaItemType::GraphicsScene2D |
                                    MetaItemType::GraphicsScene3D |
                                    MetaItemType::PhysicsItem2D  |
                                    MetaItemType::PhysicsItem3D
                       );
    }

    static inline constexpr auto meta_is_graphics_scene_based( MetaItemType itmType)
    {
        /// ## This only works if meta tracking is enabled
        return has_any( itmType, MetaItemType::GraphicsScene2D    |
                                    MetaItemType::GraphicsScene3D
                       );
    }


    static inline constexpr auto meta_is_graphics_item_or_physics( MetaItemType itmType)
    {
        /// ## This only works if meta tracking is enabled
        return has_any( itmType, MetaItemType::GraphicsItem2D     |
                                    MetaItemType::GraphicsItem3D  |
                                    MetaItemType::PhysicsItem2D   |
                                    MetaItemType::PhysicsItem3D
                       );
    }

    template<typename RetType, MetaItemType chkTp=MetaItemType::None>
    constexpr static inline RetType *castItem( CoreItem *itm)
    {
        if( QX_DEF_ENABLE_META_DEBUGGING )
        {
            const auto itmType  = itm->meta_item_type();
            bool validCast = true;

            if constexpr( std::is_same<RetType, GraphicsScene>::value )
                /// ## Special case for GraphicsScene
                /// ## Cant call castItem<, GraphicsScene2D|GraphicsScene3D>
                validCast = meta_is_graphics_scene_based( itmType );

            else if constexpr( std::is_same<RetType, GraphicsItem>::value )
                /// ## Special case for GraphicsItem
                /// ## Cant call castItem<, GraphicsItem2D|GraphicsItem3D>
                validCast = meta_is_graphics_item_based( itmType );
            else
                validCast = has_any( itmType, chkTp );

            const auto name = itm->meta_type_name();
            dbg_assert_st( validCast ) <<
                "Mismatch in castItem, between RetType and MetaItemType for item type: " <<
                name;
        }

        return static_cast<RetType*>( itm );
    }

public:
    virtual void updatePropertyStates(MetaItemType sceneType){ dbg_unused(sceneType);}

protected:
    static void stepPendings();
    static void addPendingItems();
    static void removePendingItems();


protected:
    virtual void render(Canvas *canvas) = 0;
    virtual void updateModel() = 0;

    void updateItem(MetaItemType sceneType );

protected:
    void renderItem(Canvas *cnvs);
    void renderItem();
    x_count hierarchyIndex() const;


    void clearChildren();
    void eraseChild(CoreItem *chld);
    std::vector<SmartItem> &children();
    bool isWindowItem() const;
    bool isSceneItem2D() const;
    bool isSceneItem3D() const;
    bool isSceneItem() const;


    bool isGraphicsItem2D() const;
    bool isGraphicsItem3D() const;
    bool isGraphicsItem() const;


    /// ## This creates any item, and adds to a parent
    ///
    template<typename Type>
    static Type *makeItem(CoreItem *parent)
    {
        auto ret = makeUniqueItem<Type, false>( parent );
        const auto idx = ret->hierarchyIndex();
        if( idx > QX_DEF_MAX_HIERARCHY_LEVEL )
            dbg_warning_st() << "Tree hierarchy exceeded with " << idx << " levels deep";

        const auto retPtr = ret.get();
        dbg_assert_st( parent ) << "Can't call makeItem with a null parent";
        auto &lst = parent->m_addItems;
        if( parent )
            lst.push_back( std::move( ret ) );
        return retPtr;
    }

    /// ## This creates any item
    ///
    template<typename Type, bool root>
    static std::unique_ptr<Type> makeUniqueItem(CoreItem *parent = nullptr)
    {
        std::unique_ptr<Type> ret;
        if constexpr( root )
            ret = MetaObject::make_unique_meta<Type>();
        else
            ret = MetaObject::make_unique_meta<Type>( parent );


        dbg_assert_st( ret->meta_item_type() != MetaItemType::None ) <<
            "Can't add an item with 'MetaItemType::NoneItem' (" <<
            ret->meta_type_name() << ")";

        //if( ret->meta_item_type() != MetaItemType::Root )
        //{
            /// ## ToDo: Why this code is commented out
            /// ## This will call virtual function "::parent->meta_child_type"
            /// ## in the parents constructor
            /// ## Check "meta_check_hierarchy"
            // const auto match = static_cast<bool>(parent->meta_child_type() & ret->meta_item_type());
            // dbg_assert_st( match ) <<
            //     "Item types mismatch, you can't add " <<
            //     ret->meta_type_name() << " to " <<
            //     parent->meta_type_name();
        //}
        return ret;
    }

    void meta_check_hierarchy();

private:
    static CoreItem                     *m_rootItem;
    static std::vector<SmartItem>        m_addItems;
    static std::vector<CoreItem*>        m_removedItems;
    static std::vector<SmartComp>        m_addComponents;
    static std::vector<CoreComponent*>   m_removedComponents;


    std::vector<SmartItem>   m_children;
    std::vector<SmartComp>   m_components;
    CoreItem                *m_parent;
    PropertyStates           m_propertyStates;

protected:
   ItemType             m_itemType;
};


}


#endif // COREITEM_H
