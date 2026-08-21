#include "mainwindow.h"

#include <core/graphicsitem2d.h>
#include <items/rectangle.h>
#include <core/graphicsscene2d.h>

#include <components/timer.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();

    auto cam0 = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );


    auto itm = scene->addItem<Qx::Rectangle>();;
    itm->transform.setPosition( { 20,20, 1} );


    auto dynPrprty = linearPosition( itm );
    // auto dynPrprty = bezierPosition( itm );
    // auto dynPrprty = polynomialPosition( itm );
    // auto dynPrprty = dampedPosition( itm );



    dynPrprty->dynamicPosition = {100,100,0} ;


    Qx::Timer::singleShot( 2000, [dynPrprty](){
        dynPrprty->dynamicPosition = {300,300,0} ;
    });
}

Qx::DynamicPosition<Qx::LinearEasing> *MainWindow::linearPosition(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Linear Easing
    auto dynPrprty = itm->attach<Qx::DynamicPosition<Qx::LinearEasing>>();
   dynPrprty->easing()->duration = .5 * 1000;
    return dynPrprty;
}

Qx::DynamicPosition<Qx::BezierEasing> *MainWindow::bezierPosition(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Bezier Easing
    auto dynPrprty = itm->attach<Qx::DynamicPosition<Qx::BezierEasing>>();
    auto easing =dynPrprty->easing();
   easing->control0 = {.25,.5};
   easing->control1 = { .75, 1.25};
   easing->duration = 1 * 1000;
    return dynPrprty;
}

Qx::DynamicPosition<Qx::PolynomialEasing>* MainWindow::polynomialPosition(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Polynomial Easing
    auto dynPrprty = itm->attach<Qx::DynamicPosition<Qx::PolynomialEasing>>();
    auto easing = dynPrprty->easing();
    //easing->polynomial = [](Qx::x_real x) { return x*x*x; }; /// ## Custom
   easing->polynomial = Qx::Easing::EaseOutElastic;
   easing->duration   = 2 * 1000;
    return dynPrprty;
}

Qx::DynamicPosition<Qx::DampedEasing> *MainWindow::dampedPosition(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Damped Easing
    auto dynPrprty = itm->attach<Qx::DynamicPosition<Qx::DampedEasing>>();
    auto easing = dynPrprty->easing();
   easing->init( 4, .32, 0 );
    return dynPrprty;
}
