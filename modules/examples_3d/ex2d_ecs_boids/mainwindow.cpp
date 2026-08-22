#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <core/graphicsscene3d.h>
#include <misc/collisions.h>
#include <misc/collisionstree.h>
#include <ecs/ecscollisioncomponent.h>
#include <ecs/ecscomponent.h>
#include <primitives/worlditem.h>
#include <components/cameracontroller.h>



namespace Layers {
/// ## Order is important Check Qx::BoidCollision

constexpr static Qx::x_layers Bullets    = 1 << 0;
constexpr static Qx::x_layers Enemies    = 1 << 1;
constexpr static Qx::x_layers Friendlies = 1 << 2;
constexpr static Qx::x_layers Obstacles  = 1 << 3;

}


static auto mk( const Qx::x_vector3 &ctr, Qx::x_layers lyr )
{
    Qx::BoidCollision ret;
    ret.center = ctr;
    ret.visibleRadius = 7;
    ret.boundingRadius = 1;
    ret.layer = lyr;


    ret.minspeed = 30;
    ret.maxspeed = 50;

    ret.protectedRadius = 5;
    return ret;
}


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene3D = addItem<Qx::prv::GraphicsScene3D>();
    auto vw0     = scene3D->addView();
    auto cam0    = vw0->camera();
    cam0->reset3DPerspectiveCamera( screen() );


    // using RenderItemRED = Qx::ECSModelItem<ECSRenderRED,10 * 1000,4,6>;
    // using RenderItemGRN = Qx::ECSModelItem<ECSRenderGRN,10 * 1000,4,6>;


    // auto wrldItm = scene3D->addItem<Qx::WorldItem>();
    // auto campCpm = wrldItm->attach<Qx::CameraController>();
    // campCpm->setCamera( cam0 );
    // campCpm->resetControllers();


    // auto redItm = wrldItm->addItem<RenderItemRED>();

    // Qx::BoidCollision::matchingfactor = .125;
    // Qx::BoidCollision::avoidfactor = 3.75;
    // Qx::BoidCollision::centeringfactor = 0.005;
    // Qx::BoidCollision::turnfactor = 1.4;

    // Qx::BoidCollision::worldMin = wrldItm->worldMin();
    // Qx::BoidCollision::worldMax = wrldItm->worldMax();

    // static constexpr auto collisionCallback = []( Qx::BoidCollision *cols0,
    //                                               Qx::BoidCollision *cols1,
    //                                              bool impact)
    // {
    //     if( true ){
    //         cols0->flock( cols1 );
    //         cols1->flock( cols0 );
    //     }
    // };


    // auto colCmp = wrldItm->attach<Qx::ECSCollisionComponent<Qx::BoidCollision,collisionCallback> >();
    // auto ecsCmp = wrldItm->attach<Qx::ECSComponent>();
    // auto ecsWorld = ecsCmp->ecsWorld();
    // colCmp->collisionsSource = ecsWorld;
    // redItm->setMaterial( ":/materials/glow.filamat" );
    // redItm->setPrimitiveType( Qx::PrimitiveType::Triangles );
    // // /// ## Populate with some entities...
    // for (int idx = 0; idx < 1500; ++idx){
    //     const auto xx = (10 + rand() % 10);
    //     const auto yy = (10 + rand() % 10);
    //     const auto zz = (10 + rand() % 10);
    //     // dbg_print_st() << xx;
    //     ecsWorld->entity()
    //     .set( redItm->createMeshObject() )
    //         .set<Qx::BoidCollision>( mk({xx,yy,zz}, Layers::Enemies));
    // }

    
    // ecsWorld->system<ECSRenderRED, Qx::BoidCollision>("RedEntities")
    //     .each([this](flecs::iter& it, size_t, ECSRenderRED& redObj, Qx::BoidCollision& col )
    //           {

    //         const auto dlt = it.delta_time();
    //         col.updateCenter( dlt );
    //               const auto ctr = col.center;
    //               const auto rad = col.boundingRadius;

    //               const auto vIndx = redObj.verticesIndex;
    //               const auto iIndx = redObj.indicesIndex;

    //               const auto halfWidth  = rad;
    //               const auto halfHeight = rad;
    //               const auto halfDepth  = rad;


    //               redObj.vertices[ vIndx+0 ] = {{ ctr.x - halfWidth, ctr.y - halfHeight, ctr.z - halfDepth }, { 0.0f, 0.0f }};
    //               redObj.vertices[ vIndx+1 ] = {{ ctr.x + halfWidth, ctr.y - halfHeight, ctr.z - halfDepth }, { 1.0f, 0.0f }};
    //               redObj.vertices[ vIndx+2 ] = {{ ctr.x + halfWidth, ctr.y + halfHeight, ctr.z - halfDepth }, { 1.0f, 1.0f }};
    //               redObj.vertices[ vIndx+3 ] = {{ ctr.x - halfWidth, ctr.y + halfHeight, ctr.z - halfDepth }, { 0.0f, 1.0f }};

    //               redObj.indices[ iIndx+0 ] = vIndx+0;
    //               redObj.indices[ iIndx+1 ] = vIndx+1;
    //               redObj.indices[ iIndx+2 ] = vIndx+2;
    //               redObj.indices[ iIndx+3 ] = vIndx+0;
    //               redObj.indices[ iIndx+4 ] = vIndx+2;
    //               redObj.indices[ iIndx+5 ] = vIndx+3;

    //     });

    



}
