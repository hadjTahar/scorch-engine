#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/graphicswindow.h>

#include <ecs/ecscomponent.h>

class MainWindow : public Qx::prv::GraphicsWindow
{

public:
    MainWindow(CoreItem *parent);

protected:


    flecs::query<Qx::MeshView> m_meshQuery;


    Qx::x_count m_dltCounter;
};

#endif // MAINWINDOW_H
