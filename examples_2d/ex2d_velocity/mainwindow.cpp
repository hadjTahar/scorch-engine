#include "mainwindow.h"

#include <core/graphicsitem2d.h>
#include <items/rectangle.h>
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
    itm->transform.setPosition( { 20,20, 1} );


    // auto dynPrprty = linearVelocity( itm );
    // auto dynPrprty = bezierVelocity( itm );
    auto dynPrprty = polynomialVelocity( itm );
    // auto dynPrprty = dampedVelocity( itm );



    dynPrprty->dynamicVelocity = { 1.5, 1.5, 0};
}

Qx::DynamicVelocity<Qx::LinearEasing> *MainWindow::linearVelocity(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Linear Easing
    auto dynPrprty = itm->attach<Qx::DynamicVelocity<Qx::LinearEasing>>();
   dynPrprty->easing()->duration = 2 * 1000;
    return dynPrprty;
}

Qx::DynamicVelocity<Qx::BezierEasing> *MainWindow::bezierVelocity(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Bezier Easing
    auto dynPrprty = itm->attach<Qx::DynamicVelocity<Qx::BezierEasing>>();
    auto easing =dynPrprty->easing();
   easing->control0 = {.25,.5};
   easing->control1 = { .75, 1.25};
   easing->duration = 2 * 1000;
    return dynPrprty;
}

Qx::DynamicVelocity<Qx::PolynomialEasing>* MainWindow::polynomialVelocity(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Polynomial Easing
    auto dynPrprty = itm->attach<Qx::DynamicVelocity<Qx::PolynomialEasing>>();
    auto easing = dynPrprty->easing();
    // easing->polynomial = [](Qx::x_real x) { return 3*x*x*x; }; /// ## Custom
   easing->polynomial = Qx::Easing::EaseOutElastic;
   easing->duration   = 2 * 1000;
    return dynPrprty;
}

Qx::DynamicVelocity<Qx::DampedEasing> *MainWindow::dampedVelocity(Qx::prv::GraphicsItem2D *itm)
{
    /// ## Damped Easing
    auto dynPrprty = itm->attach<Qx::DynamicVelocity<Qx::DampedEasing>>();
    auto easing = dynPrprty->easing();
   easing->init( 4, .32, 0 );
    return dynPrprty;
}
