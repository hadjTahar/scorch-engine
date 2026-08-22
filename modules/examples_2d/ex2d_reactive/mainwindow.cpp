#include "mainwindow.h"

#include <items/rectangle.h>

#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <components/timer.h>

#include <components/reactiveproperty.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    auto itm = scene->addItem<Qx::Rectangle>();

    auto cmp = itm->attach<Qx::ReactiveProperty<Qx::x_vector3>>();
    cmp->update = [itm](){return itm->transform.position(); };

    cmp->changed = [](const Qx::x_vector3 &vec)
    {
        dbg_print_st() << "CHANGED : " << vec.x;
    };


    Qx::Timer::singleShot( 3000, [itm](){
        const Qx::x_vector3 pos = itm->transform.position();
        itm->transform.setPosition( pos + Qx::x_vector3{111,111,0} );
    });
}
