#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>

MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    auto itm = scene->addItem<Qx::Rectangle>();
}
