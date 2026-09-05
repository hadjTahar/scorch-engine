#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvassdlrenderer.h>
#include <backends/canvasskiarastersurface.h>
#include <backends/canvasskiarastertexture.h>
#include <backends/canvasskiaopenglsurface.h>
#include <backends/canvasskiaopengltexture.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSDLRenderer> >();
    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterSurface> >();
    auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterTexture> >();

    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaOpenGLSurface> >();
    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaOpenGLTexture> >();

    auto vw0   = scene->addView();
    auto cam0  = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    auto itm0  = scene->addItem<Qx::Rectangle>();
    auto itm1  = itm0->addItem<Qx::Rectangle>();


    itm0->transform.setPosition( {100, 100, 0 } );
    itm0->style.setColor( Qx::red() );

    itm1->transform.setPosition( {20, 20, 0 } );
    itm1->style.setColor( Qx::green() );
}
