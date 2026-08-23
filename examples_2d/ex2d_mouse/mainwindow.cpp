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


    auto layout = scene->addItem<Qx::FlexLayout>();

    layout->style.setColor( Qx::green() );

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

    auto mCmp0 = rc0->attach<Qx::MouseComponent>();
    auto mCmp1 = rc1->attach<Qx::MouseComponent>();
    auto mCmp2 = rc2->attach<Qx::MouseComponent>();

    // mCmp0->pressed = [mCmp0](const Qx::MouseEvent &)
    // {
    //     dbg_print_st() << "pressed : " << mCmp0;
    //     return true;
    // };
    // mCmp0->released = [mCmp0](const Qx::MouseEvent &evt)
    // {
    //     dbg_print_st() << static_cast<int>(evt.clicks()) << " : released : " << mCmp0;
    //     return true;
    // };
    mCmp0->clicked = [mCmp0](const Qx::MouseEvent &evt)
    {
        dbg_print_st() << static_cast<int>(evt.clicks()) << " : clicked : " << mCmp0;
        return true;
    };

    mCmp1->clicked = [mCmp1](const Qx::MouseEvent &)
    {
        dbg_print_st() << "clicked : " << mCmp1;
        return true;
    };

    mCmp2->clicked = [mCmp2](const Qx::MouseEvent &)
    {
        dbg_print_st() << "clicked : " << mCmp2;
        return true;
    };

    mCmp2->enter = [mCmp2](const Qx::MouseEvent &evt)
    {
        dbg_print_st() << "Enter : ";
        return true;
    };

    mCmp2->leave = [mCmp2](const Qx::MouseEvent &evt)
    {
        dbg_print_st() << "Leave : ";
        return true;
    };

    mCmp2->move = [mCmp2](const Qx::MouseEvent &evt)
    {
        dbg_print_st() << "Move : ";
        return true;
    };


}
