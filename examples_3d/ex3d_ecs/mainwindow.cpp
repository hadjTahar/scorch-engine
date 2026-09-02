#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <ecs/ecscomponent.h>


#include <flecs.h>


struct Position { float x, y; };
struct Velocity { float dx, dy; };




MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    // auto scene = addItem<Qx::Backend::CanvasSDLRenderer>();
    // auto vw0 = scene->addView();
    // auto cam0 = vw0->camera();
    // auto itm = scene->addItem<Qx::Rectangle>();

    // auto ecsCmp = itm->attach<Qx::ECSComponent>();
    // auto ecsWorld = ecsCmp->ecsWorld();



    // ecsCmp->init = [ecsWorld]()
    // {
    //     dbg_print_st() << "----------------------------------";
    //     dbg_print_st() << "Init";

    //     // Populate with some entities...
    //     for (int i = 0; i < 10; ++i) {
    //         ecsWorld->entity()
    //         .set<Position>({0.0f, 0.0f})
    //             .set<Velocity>({1.0f, 1.0f});
    //     }
    // };



    // ecsCmp->preProgress = []()
    // {
    //     dbg_print_st() << "----------------------------------";
    //     dbg_print_st() << "Prepare next iteration....";
    // };

    // ecsCmp->postProgress = []()
    // {
    //     dbg_print_st() << "Clean previous iteration....";
    // };

    // // 2. Define a System using the built-in scheduler
    // // Flecs automatically multithreads this system across its worker pool
    // ecsWorld->system<Position, Velocity>("MovementSystem")
    //     .each([](flecs::iter& it, size_t, Position& pos, Velocity& vel) {
    //         // it.delta_time() can also be accessed here if needed!
    //         pos.x += vel.dx * it.delta_time();
    //         pos.y += vel.dy * it.delta_time();

    //         dbg_print_st() << pos.x;
    //     });


}
