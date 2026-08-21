#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <components/keycomponent.h>
#include <components/statemachinecomponent.h>
#include <misc/keyevent.h>


#include <iostream>



struct StartWalk {};
struct StopMove {};

struct Duck {};
struct Stand {};

struct StartShooting {};
struct FinishShooting {};

// Define State Groups
struct Halt {}; struct Walking {}; struct Running {}; struct Charging {};
struct Standing {}; struct Ducking {}; struct Jumping {};
struct Noattack {}; struct Shooting {}; struct Reloading {};

struct PlayerController {
    auto operator()() const {
        using namespace Qx::sml;


        auto on_Walking = [](Qx::prv::GraphicsItem *item) {
            dbg_print() << item << "Player started Walking!\n ";
        };

        auto on_Shooting = [](Qx::prv::GraphicsItem *item) {
            dbg_print() << item << "Player started Shooting!\n ";
        };


        return make_transition_table(
            // Motion Region
            *state<Halt> + event<StartWalk> = state<Walking>,
            state<Walking> + event<StopMove> = state<Halt>,

            // Stance Region
            *state<Standing> + event<Duck> = state<Ducking>,
            state<Ducking> + event<Stand> = state<Standing>,

            // Action Region
            *state<Noattack> + event<StartShooting> = state<Shooting>,
            state<Shooting> + event<StartShooting> = state<Shooting>,
            state<Shooting> + event<FinishShooting> = state<Noattack>,


            state<Walking> + on_entry<_> / on_Walking,
            state<Shooting> + on_entry<_> / on_Shooting

            );
    }
};




MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    auto itm = scene->addItem<Qx::Rectangle>();


    auto stCmp = itm->attach<Qx::StateMachineComponent<PlayerController>>();
    stCmp->processEvent<Standing>();
    stCmp->processEvent<StartWalk>();


    auto mCmp0 = itm->attach<Qx::KeyComponent>();

    mCmp0->keyPressed = [stCmp](const Qx::KeyEvent &evt)
    {
        stCmp->processEvent<StartShooting>();
        return true;
    };
    mCmp0->keyReleased = [stCmp](const Qx::KeyEvent &evt)
    {
        stCmp->processEvent<FinishShooting>();
        return true;
    };

    mCmp0->setFocused( true );
}
