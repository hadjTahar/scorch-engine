#include "mainwindow.h"

#include "images.h"
#include <items/image.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );

    auto sldItm = scene->addItem<ImageRectangle>();
    sldItm->transform.setPosition( {0, 0, 0 } );

    auto imgItm = scene->addItem<Qx::Image>();
    imgItm->transform.setPosition( {0, 200, 0 } );

    imgItm->style.setSource( ":/images/test.png" );
    imgItm->transform.setSize( {-1, -1} );

}
