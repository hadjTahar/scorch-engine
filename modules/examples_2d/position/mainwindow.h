#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/graphicsitem2d.h>
#include <core/windowitem.h>

#include <components/dynamicposition.h>

#include <easing/lineareasing.h>
#include <easing/beziereasing.h>
#include <easing/polynomialeasing.h>
#include <easing/dampedeasing.h>


class MainWindow : public Qx::prv::WindowItem
{

public:
    MainWindow(CoreItem *parent);

protected:

    Qx::DynamicPosition<Qx::LinearEasing>     *linearPosition(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicPosition<Qx::BezierEasing>     *bezierPosition(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicPosition<Qx::PolynomialEasing> *polynomialPosition(Qx::prv::GraphicsItem2D *itm);
    Qx::DynamicPosition<Qx::DampedEasing>     *dampedPosition(Qx::prv::GraphicsItem2D *itm);
};

#endif // MAINWINDOW_H
