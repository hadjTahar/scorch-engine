#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/graphicsitem2d.h>
#include <core/graphicswindow.h>

#include <components/dynamicproperty.h>

#include <easing/lineareasing.h>
#include <easing/beziereasing.h>
#include <easing/polynomialeasing.h>
#include <easing/dampedeasing.h>


class MainWindow : public Qx::prv::GraphicsWindow
{

public:
    MainWindow(CoreItem *parent);

protected:

    Qx::DynamicProperty<Qx::LinearEasing>     *linearProperty(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicProperty<Qx::BezierEasing>     *bezierProperty(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicProperty<Qx::PolynomialEasing> *polynomialProperty(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicProperty<Qx::DampedEasing>     *dampedProperty(Qx::prv::GraphicsItem2D *itm);
};

#endif // MAINWINDOW_H
