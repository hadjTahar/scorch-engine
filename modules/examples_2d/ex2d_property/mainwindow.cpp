#include "mainwindow.h"

#include <core/graphicsitem2d.h>
#include <items/rectangle.h>
#include <core/graphicsscene2d.h>

#include <components/cameracontroller.h>
#include <components/timer.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();

    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );

    auto itm = scene->addItem<Qx::Rectangle>();
    itm->transform.setPosition( { 20,20, 1} );

    auto campCpm = itm->attach<Qx::CameraController>();
    campCpm->setCamera( cam0 );
    campCpm->resetControllers();


    // auto dynPrprty = linearProperty( itm );
    // auto dynPrprty = bezierProperty( itm );
    // auto dynPrprty = polynomialProperty( itm );
    auto dynPrprty = dampedProperty( itm );



    dynPrprty->reset = false;
    dynPrprty->value = 100 ;

    dynPrprty->progress = [itm](Qx::x_real val, bool done)
    {
        dbg_print_st() << "progress : " << val << " : " << done;
        itm->transform.setPosition( { val, val, 0} );
    };

    Qx::Timer::singleShot( 3000, [dynPrprty](){
        dynPrprty->value = 300 ;
    });
}

Qx::DynamicProperty<Qx::LinearEasing> *MainWindow::linearProperty(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Linear Easing
    auto dynPrprty = itm->attach<Qx::DynamicProperty<Qx::LinearEasing>>();
    dynPrprty->easing()->duration = .5 * 1000;
    return dynPrprty;
}

Qx::DynamicProperty<Qx::BezierEasing> *MainWindow::bezierProperty(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Bezier Easing
    auto dynPrprty = itm->attach<Qx::DynamicProperty<Qx::BezierEasing>>();
    auto easing =dynPrprty->easing();
    easing->control0 = {.25,.5};
    easing->control1 = { .75, 1.25};
    easing->duration = 1 * 1000;
    return dynPrprty;
}

Qx::DynamicProperty<Qx::PolynomialEasing>* MainWindow::polynomialProperty(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Polynomial Easing
    auto dynPrprty = itm->attach<Qx::DynamicProperty<Qx::PolynomialEasing>>();
    auto easing = dynPrprty->easing();
    //easing->polynomial = [](Qx::x_real x) { return x*x*x; }; /// ## Custom
    easing->polynomial = Qx::Easing::EaseOutElastic;
    easing->duration   = 2 * 1000;
    return dynPrprty;
}

Qx::DynamicProperty<Qx::DampedEasing> *MainWindow::dampedProperty(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Damped Easing
    auto dynPrprty = itm->attach<Qx::DynamicProperty<Qx::DampedEasing>>();
    auto easing = dynPrprty->easing();
    easing->init( 4, .32, 0 );
    return dynPrprty;
}
