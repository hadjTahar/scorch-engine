#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <misc/collisions.h>
#include <misc/collisionstree.h>
#include <ecs/ecscollisioncomponent.h>
#include <ecs/ecscomponent.h>


enum class EntityType {None, Bullet, Enemy1, Enemy2,  };


namespace Layers {
/// ## Order is important Check Qx::Collision

constexpr static Qx::x_layers Bullets    = 1 << 0;
constexpr static Qx::x_layers Enemies    = 1 << 1;
constexpr static Qx::x_layers Friendlies = 1 << 2;
constexpr static Qx::x_layers Obstacles  = 1 << 3;



}

struct TaggedCollision : Qx::Collision
{
    // TaggedCollision(Qx::Collision col): Qx::Collision{col}{}

    static auto mk( const Qx::x_vector3 &ctr, EntityType entTp, Qx::x_layers lyr )
    {
        TaggedCollision ret;
        ret.center = ctr;
        ret.visibleRadius = 1;
        ret.boundingRadius = 1;
        ret.layer = lyr;

        ret.entityType = entTp;
        return ret;
    }
    EntityType entityType;
};

MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    // auto scene = addItem<Qx::prv::GraphicsScene2D>();
    // auto vw0 = scene->addView();
    // auto cam0 = vw0->camera();
    // auto itm = scene->addItem<Qx::Rectangle>();


    // static constexpr auto collisionCallback = [](TaggedCollision *clsn0,
    //                                              TaggedCollision *clsn1,
    //                                              bool impact)
    // {
    //     /// ## Handle behavior as data
    //     /// ## Eg, position, velocity, bullets damage (accumulate), .....
    //     /// ## Then query the collisions, and handle them, using ::system
    //     ///

    //     /// ## We only care for impacts
    //     if( !impact )
    //         return;


    //     if( clsn0->entityType == EntityType::Bullet ){
    //         const auto enmTp = clsn1->entityType == EntityType::Enemy1 ||
    //                            clsn1->entityType == EntityType::Enemy2;
    //         if( enmTp ){
    //             /// ## Mark clsn0 for destruction, in ::system{e.destruct()}
    //             /// ## clsn1 takes accumulated damage
    //             dbg_print_st() << clsn0 << " bullet impact with enemy " << clsn1;
    //         }
    //     }

    //     else if( clsn1->entityType == EntityType::Bullet ){
    //         const auto enmTp = clsn0->entityType == EntityType::Enemy1 ||
    //                            clsn0->entityType == EntityType::Enemy2;
    //         if( enmTp ){
    //             /// ## Mark clsn1 for destruction, in ::system{e.destruct()}
    //             /// ## clsn0 takes accumulated damage
    //             dbg_print_st() << clsn1 << " bullet impact with enemy " << clsn0;
    //         }
    //     }

    // };


    // auto colCmp = itm->attach<Qx::ECSCollisionComponent<TaggedCollision,collisionCallback> >();
    // auto ecsCmp = itm->attach<Qx::ECSComponent>();
    // auto ecsWorld = ecsCmp->ecsWorld();
    // colCmp->collisionsSource = ecsWorld;


    // /// ## Populate with some entities...
    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({1.0, 2.0, 3.0}, EntityType::Enemy1, Layers::Enemies));


    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({4.0, 5.0, 6.0}, EntityType::Enemy1, Layers::Enemies));
    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({10.0, 11.0, 12.0}, EntityType::Enemy1, Layers::Enemies));

    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({1.1, 2.1, 3.1}, EntityType::Enemy1, Layers::Enemies));
    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({1.1, 2.1, 3.1}, EntityType::Enemy2, Layers::Enemies));
    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({1.1, 2.1, 3.1}, EntityType::Enemy2, Layers::Enemies));

    // ecsWorld->entity()
    //     .set<TaggedCollision>(TaggedCollision::mk({1.1, 2.1, 3.1}, EntityType::Bullet,  Layers::Bullets));


    // ecsWorld->system<TaggedCollision>("RedEntities")
    //     .each([this](TaggedCollision& col )
    //           {
    //               /// ## Removed impacted bullets
    //               /// ## Take damage
    //           });

}
