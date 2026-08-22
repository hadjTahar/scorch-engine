#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <misc/ui/uiwindow.h>
#include <core/cameras/g2dcamera.h>




using x_real = Qx::x_real;
class Qx::G2DGraphicsManager;

class MainWindow : public Qx::UIWindow
{
public:
    MainWindow();

protected:
    void setup() override;

protected:
};

#endif // MAINWINDOW_H
