#include "mainwindow.h"

#include <misc/hostenv.h>

MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    dbg_print() << "App Name: " << Qx::HostEnv::App::appName();
    dbg_print() << "ORG Name: "  << Qx::HostEnv::App::orgName();
    dbg_print() << "App Path: "  << Qx::HostEnv::App::path();

    dbg_print() << "--------------------------" ;
    dbg_print() << "OS Name: " << Qx::HostEnv::OS::name();
    dbg_print() << "OS Arch: " << Qx::HostEnv::OS::arch();


    dbg_print() << "--------------------------" ;
    dbg_print() << "User Name: " << Qx::HostEnv::User::name();
    dbg_print() << "User Data: " << Qx::HostEnv::User::data();
    dbg_print() << "User DB:   " << Qx::HostEnv::User::dbProfile();
    dbg_print() << "User Home: " << Qx::HostEnv::User::home();
    dbg_print() << "User Desktop: " << Qx::HostEnv::User::desktop();
    dbg_print() << "User Docs: " << Qx::HostEnv::User::documents();
    dbg_print() << "User Downloads: " << Qx::HostEnv::User::downloads();
    dbg_print() << "User Musci: " << Qx::HostEnv::User::music();
    dbg_print() << "User Picture: " << Qx::HostEnv::User::pictures();
    // dbg_print() << "User publicShare: " << Qx::HostEnv::User::publicShare();
    dbg_print() << "User Saved Games: " << Qx::HostEnv::User::savedGames();
    dbg_print() << "User Screen shots: " << Qx::HostEnv::User::screenShots();
    dbg_print() << "User Templates: " << Qx::HostEnv::User::templates();
    dbg_print() << "User Videos: " << Qx::HostEnv::User::videos();

    dbg_print() << "--------------------------" ;


}
