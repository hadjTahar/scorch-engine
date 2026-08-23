#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/graphicsitem2d.h>
#include <core/windowitem.h>

#include <components/dynamicvelocity.h>

#include <easing/lineareasing.h>
#include <easing/beziereasing.h>
#include <easing/polynomialeasing.h>
#include <easing/dampedeasing.h>


class MainWindow : public Qx::prv::WindowItem
{

public:
    MainWindow(CoreItem *parent);

protected:

    Qx::DynamicVelocity<Qx::LinearEasing>     *linearVelocity(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicVelocity<Qx::BezierEasing>     *bezierVelocity(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicVelocity<Qx::PolynomialEasing> *polynomialVelocity(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicVelocity<Qx::DampedEasing>     *dampedVelocity(Qx::prv::GraphicsItem2D *itm);
};

#endif // MAINWINDOW_H
