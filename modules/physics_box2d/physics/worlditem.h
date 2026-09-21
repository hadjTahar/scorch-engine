#ifndef WORLDITEM_H
#define WORLDITEM_H

#include <items/rectangle.h>
#include <box2dcpp/world.h>


namespace Qx::Box2D {

class PhysicsComponent;

class WorldItem : public Rectangle
{
    QX_META_OBJECT( "WorldItem",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::PhysicsItem2D )

private:
    using CoreItem::addItem;
    // using Rectangle::addItem;

public:
    WorldItem(CoreItem *parent);

    template <typename ItemType>
    ItemType *addBodyItem()
    {
        auto ret = addItem<ItemType>();
        ret->m_body = m_world->addBody();
        return ret;
    }


public:
    prv::x_simpleCallback step;


    World *world() const;


    x_vector3 worldView() const;
    void setWorldView(const x_vector3 &newWorldView);

    x_vector3 worldAxis() const;
    void setWorldAxis(const x_vector3 &newWorldAxis);

private:
    x_matrix4x4 m_prevMat;
    x_vector3   m_worldAxis;
    PhysicsComponent *m_physicsComponent;
    World            *m_world;
};

}

#endif // WORLDITEM_H
