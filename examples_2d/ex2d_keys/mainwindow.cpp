#include "mainwindow.h"

#include <items/flexlayout.h>
#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <components/keycomponent.h>
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

    auto mCmp0 = rc0->attach<Qx::KeyComponent>();
    auto mCmp1 = rc1->attach<Qx::KeyComponent>();
    auto mCmp2 = rc2->attach<Qx::KeyComponent>();

    mCmp0->keyPressed = [mCmp0](const Qx::KeyEvent &evt)
    {
        dbg_print_st()<< evt.key() << " pressed : " << mCmp0;
        return true;
    };
    mCmp1->keyReleased = [mCmp1](const Qx::KeyEvent &evt)
    {
        dbg_print_st()<< (char)evt.key() << " released : " << mCmp1;
        if( static_cast<Qx::Key>(evt.key()) == Qx::Key::KEY_V)
            dbg_print_st()<< "V";
        return true;
    };

    mCmp1->sequence = [mCmp1](const Qx::SequenceEvent &seq)
    {
        dbg_print_st() << ": ++ " << seq.index;
        return true;
    };

    mCmp1->setFocusPolicy( Qx::FocusPolicy::Click );
    mCmp1->setFocused( true );


}
