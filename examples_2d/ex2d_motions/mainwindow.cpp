#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvasskiarastersurface.h>

#include <components/steeringmotion.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene  = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterSurface> >();
    auto vw0    = scene->addView();
    auto cam0   = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    auto itm    = scene->addItem<Qx::Rectangle>();;


    itm->attach<Qx::prv::SteeringMotion>();

    // itm->transform.position = {5,5,1};
    dbg_print() << itm;
    dbg_print() << "++++++++++++++++++++++";
}
