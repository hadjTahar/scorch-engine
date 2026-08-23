#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/graphicswindow.h>


class MainWindow : public Qx::prv::GraphicsWindow
{

public:
    MainWindow(CoreItem *parent);

    void printCurrentTime();
};

#endif // MAINWINDOW_H
