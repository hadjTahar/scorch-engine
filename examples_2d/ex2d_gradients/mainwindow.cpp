#include "mainwindow.h"

#include "rectangles.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );

    auto sldItm = scene->addItem<SolidRectangle>();
    auto linItm = scene->addItem<LinearRectangle>();
    auto radItm = scene->addItem<RadialRectangle>();
    auto conItm = scene->addItem<ConicalRectangle>();
    auto swpItm = scene->addItem<SweepRectangle>();

    const auto sz = sldItm->transform.size();
    const auto ww = sz.width;

    sldItm->transform.setPosition( {10,        10, 220 } );
    linItm->transform.setPosition( {20 +   ww, 10, 220 } );
    radItm->transform.setPosition( {30 + 2*ww, 10, 220 } );
    conItm->transform.setPosition( {30 + 3*ww, 10, 220 } );
    swpItm->transform.setPosition( {30 + 4*ww, 10, 220 } );
}
