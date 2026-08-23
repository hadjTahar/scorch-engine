#include "mainwindow.h"

#include <items/flexlayout.h>
#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <components/mousecomponent.h>
#include <components/timer.h>
#include <misc/mouseevent.h>

MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0  = scene->addView();
    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );


    /// ------------------------------------------
    auto layout = scene->addItem<Qx::FlexLayout>();
    layout->style.setColor( Qx::yellow() );

    auto rc0 = layout->addItem<Qx::Rectangle>();
    auto rc1 = layout->addItem<Qx::Rectangle>();
    auto rc2 = layout->addItem<Qx::Rectangle>();



    layout->flexStyle()->flexDirection = Qx::FlexDirection::Row;
    layout->flexStyle()->centerItems();

    rc0->flexStyle()->width  = Qx::FlexSize::pixels( 100 );
    rc0->flexStyle()->height = Qx::FlexSize::pixels( 100 );
    rc1->flexStyle()->width  = Qx::FlexSize::pixels( 100 );
    rc1->flexStyle()->height = Qx::FlexSize::pixels( 100 );
    rc2->flexStyle()->width  = Qx::FlexSize::pixels( 100 );
    rc2->flexStyle()->height = Qx::FlexSize::pixels( 100 );

    rc0->attach<Qx::MouseComponent>()->clicked = [rc0](const Qx::MouseEvent &evt)
    {
        if( evt.clicks() == 2 )
            rc0->removeItem();
        return true;
    };
    rc1->attach<Qx::MouseComponent>()->clicked = [rc1](const Qx::MouseEvent &evt)
    {
        if( evt.clicks() == 2 )
            rc1->removeItem();
        return true;
    };
    rc2->attach<Qx::MouseComponent>()->clicked = [rc2](const Qx::MouseEvent &evt)
    {
        if( evt.clicks() == 2 )
            rc2->removeItem();
        return true;
    };


}
