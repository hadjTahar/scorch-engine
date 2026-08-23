#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>

#include <sample_call.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    Qx::mod_sample::testPrint();


    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    auto itm0 = scene->addItem<Qx::Rectangle>();
    auto itm1 = itm0->addItem<Qx::Rectangle>();


    itm0->transform.setPosition( {100, 100, 0 } );
    itm0->style.setColor( Qx::red() );

    itm1->transform.setPosition( {20, 20, 0 } );
    itm1->style.setColor( Qx::green() );
}
