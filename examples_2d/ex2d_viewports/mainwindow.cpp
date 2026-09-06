#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvassdlrenderer.h>
#include <backends/canvasskiarastersurface.h>
#include <backends/canvasskiarastertexture.h>
#include <backends/canvasskiaopenglsurface.h>
#include <backends/canvasskiaopengltexture.h>
#include <components/mousecomponent.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSDLRenderer> >();
    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterSurface> >();
    auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterTexture> >();

    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaOpenGLSurface> >();
    // auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaOpenGLTexture> >();

    /// ## Viewport 0
    ///
    auto vw0   = scene->addView();
    auto cam0  = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    vw0->setViewport( {122.0, 122.0, 200, 200 } );
    vw0->setType( Qx::ViewType::Absolute );
    vw0->setLogicalSize( {200
                         ,200} );

    /// ## Viewport 1
    ///
    auto vw1   = scene->addView();
    vw1->camera()->reset2DOrthoCamera( screen() );
    vw1->setViewport( {522.0, 122.0, 200, 200 } );
    vw1->setType( Qx::ViewType::Absolute );
    vw1->setLogicalSize( {200
                         ,200} );

    /// ## Viewport 2
    ///
    auto vw2   = scene->addView();
    vw2->camera()->reset2DOrthoCamera( screen() );
    vw2->setViewport( {.5, .5, .5, .5} );
    vw2->setType( Qx::ViewType::Relative );
    vw2->setLogicalSize( {1920
                         ,1080} );


    auto itm0  = scene->addItem<Qx::Rectangle>();
    auto itm1  = itm0->addItem<Qx::Rectangle>();


    itm0->transform.setPosition( {100, 100, 0 } );
    itm0->style.setColor( Qx::red() );

    itm1->transform.setPosition( {250, 250, 0 } );
    itm1->style.setColor( Qx::green() );

    auto cmp0 = itm0->attach<Qx::MouseComponent>();
    auto cmp1 = itm1->attach<Qx::MouseComponent>();

    cmp0->clicked = [](const Qx::MouseEvent &event)
    {
        dbg_print_st() << "RED ITEM CLICKED";
        return true;
    };

    cmp1->clicked = [](const Qx::MouseEvent &event)
    {
        dbg_print_st() << "GREEN ITEM CLICKED";
        return true;
    };
}
