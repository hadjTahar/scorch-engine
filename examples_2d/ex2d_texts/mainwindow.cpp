#include "mainwindow.h"

#include "texts.h"

#include <items/rectangle.h>
#include <items/text.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvasskiarastersurface.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene  = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterSurface> >();
    auto vw0    = scene->addView();
    auto cam0   = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );

    auto sldItm = scene->addItem<TextRectangle>();
    sldItm->transform.setPosition( {0, 0, 0 } );


    auto textItem = scene->addItem<Qx::Text>();
    textItem->transform.setPosition( {150, 0, 0 } );
    textItem->style.setText( "Text Item" );

    textItem->style.setColor( Qx::blue() );
    textItem->transform.setSize( {200,50} );
    textItem->style.setHAlign( Qx::TextHAlign::Center );
    textItem->style.setVAlign( Qx::TextVAlign::Middle );

}
