#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include "coreitem.h"
#include <properties/itemtransform.h>



namespace Qx{
class MouseEvent;
}

namespace Qx::prv
{
class GraphicsScene;

class GraphicsItem : public prv::CoreItem
{

    friend class GraphicsWindow;
    template <typename CanvasType>
    friend class GraphicsScene2D;

    template <typename BackendType>
    friend class GraphicsScene3D;



public:
    GraphicsItem(CoreItem *parent);
    ~GraphicsItem();
    GraphicsItem *graphicsParentItem();
    void updateRender();

    template<typename Type> Type *attach()
    {
        if( QX_DEF_ENABLE_META_DEBUGGING )
        {
            // const auto valid = isGraphicsItemOrPhysics( meta_item_type() );
            const auto valid = meta_is_graphics_item_based( meta_item_type() );
            dbg_assert_st( valid ) << "Components can only be added to graphics or physics items";
        }


        auto cmp = MetaObject::make_unique_meta<Type>( this );
        auto ret = cmp.get();
        m_addComponents.push_back( std::move(cmp) );
        return ret;
    }

    void updateProperties();
    virtual bool contains(const x_vector3 &pt ) const;


protected:

    void handleMouseEvent( const MouseEvent &event);
    void updateScreenSize(ScreenSize sz );



    x_real cameraZValue() const;
    void   setCameraZValue(x_real newCameraZValue);

protected:
    void updatePropertyStates( MetaItemType sceneTp ) override final;
    virtual void screenSizeChanged(){}
    virtual void mouseEvent( const MouseEvent &event ){ dbg_unused( event );}

private:
    static bool isSceneType(MetaItemType tp);

public:
    ItemTransform   transform;
    ItemRendering   rendering;
    ScreenSize      m_screenSize;

protected:
    GraphicsScene  *m_graphicsScene;
    x_real          m_cameraZValue;
};

}
#endif // GRAPHICSITEM_H
