#include "mainwindow.h"

#include <items/rectangle.h>
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
    cam0->resetUICamera( screen() );
    auto itm    = scene->addItem<Qx::Rectangle>();


    auto itm_z_3 = itm->addItem<Qx::Rectangle>();
        auto itm_z_4 = itm_z_3->addItem<Qx::Rectangle>();
    auto itm_z_2 = itm->addItem<Qx::Rectangle>();
    auto itm_z_1 = itm->addItem<Qx::Rectangle>();


    /// ## If 2D_Z_SORTING is NOT enabled, we should see
    /// ## from back to front (red, green then blue),
    /// ## in the order they were added in
    /// ## the z coordinate is ignored
    ///
    /// ## If 2D_Z_SORTING is ENABLED, we should see
    /// ## from back to front (blue, green then red),
    /// ## in the order of the z coordinate
    ///
    ///
    itm_z_3->style.setColor( Qx::red() );
        itm_z_4->style.setColor( Qx::yellow() );
    itm_z_2->style.setColor( Qx::green() );
    itm_z_1->style.setColor( Qx::blue() );

    itm_z_3->transform.setPosition( {0,0,3} );
        itm_z_4->transform.setPosition( {20,20,5} );
    itm_z_2->transform.setPosition( {50,50,2} );
    itm_z_1->transform.setPosition( {100,100,1} );
}
