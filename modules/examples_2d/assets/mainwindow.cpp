#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>


#include <misc/assets.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    auto cam0 = vw0->camera();
    auto itm = scene->addItem<Qx::Rectangle>();



    dbg_print() << Qx::Assets::load( ":/sample0.md" ).dataText();
    dbg_print() << Qx::Assets::load( ":/sample/sample1.md" ).dataText();

    auto &ref = Qx::Assets::load( ":/sample/sample1.md" ).data();
    dbg_print() << &ref;


    dbg_print() << "++++++++ : " << Qx::Assets::fileNames( ":/sample" ).size();

}
