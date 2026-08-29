#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvasskiarastersurface.h>

#include <components/timer.h>


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    auto scene  = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterSurface> >();
    auto vw0    = scene->addView();
    auto cam0   = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    auto itm    = scene->addItem<Qx::Rectangle>();;
    auto pCmp   = itm->attach<Qx::prv::CoreComponent>();



    itm->style.setColor( Qx::green() );


    pCmp->process = [cam0](Qx::x_real dlt)
    {
        const Qx::x_vector3 pos = cam0->properties.position();
        cam0->properties.setPosition( { pos.x+.71,pos.y+.71, pos.z } );
    };


    for (int idx = 0; idx < 7; ++idx)
    {
        auto itm0 = itm->addItem<Qx::Rectangle>();;
        itm0->transform.setPosition( { idx * 50,
                                    idx * 50,
                                    0} );
        // itm0->attach<CoreComponent>();
    }
    itm->transform.setPosition( { 20,20, 1} );



    // auto timer = itm->attach<Qx::Timer>();
    // timer->start( 22222, 50 );
    // timer->timeout = [itm]{

    //     // const x_vector3 pos = itm->transform.position;
    //     // itm->transform.position = {
    //     //     pos.x+2.71,
    //     //     pos.y+2.71,
    //     //     pos.z
    //     // };

    // };


    // Qx::Timer::singleShot( 1000, [](){
    // });




    // auto vw1 = scene->addView();
    // auto cam1 = vw1->camera();
    // cam1->reset2DOrthoCamera( screen() );

    // cam1->properties.position = { -400, -400, 1 };
}
