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


struct ECSPosition : Qx::x_vector3
{
};


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene3D = addItem<Qx::prv::GraphicsScene3D>();
    auto vw0  = scene3D->addView();
    auto cam0 = vw0->camera();
    cam0->reset3DPerspectiveCamera( screen() );




    auto wrldItm = scene3D->addItem<Qx::WorldItem>();
    auto campCpm = wrldItm->attach <Qx::CameraController>();
    campCpm->setCamera( cam0 );
    campCpm->resetControllers();


    auto ecsRdrItm = scene3D->addItem<Qx::prv::GraphicsItem3D>();
    auto ecsCmp    = ecsRdrItm->attach<Qx::ECSComponent>();

    /// ## Prepare model
    auto model     = ecsRdrItm->graphicsModel();

    model->shaderSource = ":/materials/glow.filamat";
    model->shaderName   = "glow";


    model->aabb = {{ -1000, -1000, -1000 },  { 1000,1000, 1000 }};

    model->enableIndices   = true;
    model->enablePositions = true;
    model->enableUVS       = true;
    model->autoReset       = false;

    model->culling = true;
    model->changed = true;
    model->ready   = false;
    model->primitiveType = Qx::v_primitive::Triangles;

    /// ## ----------------------------------

    auto ecsWorld  = ecsCmp->ecsWorld();

    ecsCmp->init = [ecsWorld,model]()
    {
        dbg_print_st() << "----------------------------------";
        dbg_print_st() << "Init..." ;
        model->ready = false;

        // Populate (once) with some entities...
        const Qx::x_count cnt = 2500;
        model->initModel( cnt*4, cnt*6 );
        model->resetMeshCounters();
        for (int idx = 0; idx < cnt; ++idx) {
            ECSPosition pos;
            pos.x = rand() % 200 - 100;
            pos.y = rand() % 200 - 100;
            pos.z = rand() % 200 - 100;

            ecsWorld->entity()
                .set<Qx::MeshView>(model->requestMesh( 4, 6 ))
                .set<ECSPosition>(pos);
        }
    };

    ecsCmp->preProgress = [ecsWorld,model]()
    {
        model->ready = true;
    };


    ecsWorld->system<Qx::MeshView, ECSPosition>("MovementSystem")
        .each([](flecs::iter& it, size_t, Qx::MeshView& mesh, ECSPosition &pos ) {

            mesh.setVertexPositionAt( 0, {0.0f, 0.0f,  100.0f} );
            mesh.setVertexPositionAt( 1, {10.f, 0.0f,  100.0f} );
            mesh.setVertexPositionAt( 2, {10.f, 10.f,  100.0f} );
            mesh.setVertexPositionAt( 3, {0.0f, 10.0f, 100.0f} );

            mesh.translate( pos );


            mesh.setVertexUVAt(0, { 0.0f, 0.00f } );
            mesh.setVertexUVAt(1, { 1.f,  0.00f } );
            mesh.setVertexUVAt(2, { 1.f,  1.00f } );
            mesh.setVertexUVAt(3, { 0.0f, 1.00f } );

            mesh.setIndexAt( 0, 0 );
            mesh.setIndexAt( 1, 1 );
            mesh.setIndexAt( 2, 2 );

            mesh.setIndexAt( 3, 0 );
            mesh.setIndexAt( 4, 2 );
            mesh.setIndexAt( 5, 3 );

        });



}
