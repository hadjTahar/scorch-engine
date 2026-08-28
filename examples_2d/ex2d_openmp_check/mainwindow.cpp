#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvasskiarastersurface.h>

#include <omp.h>

void testOMP()
{

    // omp_set_num_threads(8);

    // This block only executes once if OpenMP is off
// #pragma omp single
//     {
//         dbg_print() << "OpenMP is active with "
//                   << omp_get_num_threads()
//                   << " threads.\n";
//     }


#pragma omp parallel
    {
        while(true) {
            // Do dummy math to keep the core busy
            volatile int x = 0;
            x++;
        }
    }
}
MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene  = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterSurface> >();
    auto vw0    = scene->addView();
    auto cam0   = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    auto itm    = scene->addItem<Qx::Rectangle>();

    testOMP();
}
