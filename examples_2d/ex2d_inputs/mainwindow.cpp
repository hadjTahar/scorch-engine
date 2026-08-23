#include "mainwindow.h"

#include <items/flexlayout.h>
#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <components/inputeventcomponent.h>
#include <components/mousecomponent.h>
#include <components/timer.h>
#include <misc/keyevent.h>
#include <misc/mouseevent.h>
#include <misc/keys.h>
#include <misc/sequenceevent.h>

MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0  = scene->addView();
    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );


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


    enum class Actions{Jump, Duck, Shoot};
    auto mCmp0 = rc0->attach<Qx::InputEventComponent<Qx::x_string>>();
    auto mCmp1 = rc1->attach<Qx::InputEventComponent<int>>();
    auto mCmp2 = rc2->attach<Qx::InputEventComponent<Actions>>();

    /// ## -----------------------------------------------
    /// ## Godot like inputs
    ///
    mCmp0->addInput( "move_forward",
                    Qx::MouseButton::Left,
                    Qx::MouseEventType::MouseClick);
    mCmp0->addInput( "move_backward", "S" );
    /// ## Not implemented yet
    mCmp0->addInput( "move_left", "CTRL+L" );



    mCmp0->process = [mCmp0](Qx::x_real )
    {
        if( mCmp0->checkAction( "move_forward" ) )
            dbg_print_st() << "Moving Forward";
        if( mCmp0->checkAction( "move_backward" ) )
            dbg_print_st() << "Moving Backward";
        if( mCmp0->checkAction( "move_left" ) )
            dbg_print_st() << "Moving Left";
    };
    /// ## -----------------------------------------------

    mCmp1->addInput( 0,
                    Qx::MouseButton::Left,
                    Qx::MouseEventType::MouseClick);
    mCmp1->addInput( 1, "S" );
    /// ## Not implemented yet
    mCmp1->addInput( 2, "CTRL+L" );
    mCmp1->process = [mCmp1](Qx::x_real )
    {
        if( mCmp1->checkAction( 0 ) )
            dbg_print_st() << "Index : " << 0;
        if( mCmp1->checkAction( 1 ) )
            dbg_print_st() << "Index : " << 1;
        if( mCmp1->checkAction( 2 ) )
            dbg_print_st() << "Index : " << 2;
    };

    /// ## -----------------------------------------------

    mCmp2->addInput( Actions::Jump,
                    Qx::MouseButton::Left,
                    Qx::MouseEventType::MouseClick);
    mCmp2->addInput( Actions::Duck, "S" );
    /// ## Not implemented yet
    mCmp2->addInput( Actions::Shoot, "CTRL+L" );
    mCmp2->process = [mCmp2](Qx::x_real )
    {
        if( mCmp2->checkAction( Actions::Jump ) )
            dbg_print_st() << "Action : " << 0;
        if( mCmp2->checkAction( Actions::Duck ) )
            dbg_print_st() << "Action : " << 1;
        if( mCmp2->checkAction( Actions::Shoot ) )
            dbg_print_st() << "Action : " << 2;
    };
    /// ## -----------------------------------------------


}
