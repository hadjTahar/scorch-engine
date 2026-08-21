#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>

#include <components/timer.h>

#include <ctime>
#include <iomanip>
#include <chrono>
#include <iostream>




MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene = addItem<Qx::prv::GraphicsScene2D>();
    auto vw0 = scene->addView();
    // auto cam0 = vw0->camera();
    auto itm = scene->addItem<Qx::Rectangle>();;

    auto timer = itm->attach<Qx::Timer>();
    timer->start( 22222, 1000 );
    timer->timeout = [this,itm]
    {

        printCurrentTime();
        const Qx::x_vector3 pos = itm->transform.position();
        itm->transform.setPosition( {
            pos.x+2.71,
            pos.y+2.71,
            pos.z
        });
    };


    Qx::Timer::singleShot( 1000, [](){
    });
}

void MainWindow::printCurrentTime()
{
    using namespace std::chrono;

    // Get current time with milliseconds
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::time_t t = system_clock::to_time_t(now);
    std::tm localTime{};

#if defined(_WIN32)
    localtime_s(&localTime, &t);
#else
    localtime_r(&t, &localTime);
#endif

    std::cout
        << std::put_time(&localTime, "%H:%M:%S")
        << '.'
        << std::setw(3) << std::setfill('0') << ms.count()
        << '\n';
}
