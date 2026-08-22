#include "mainwindow.h"
#include "circles.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene3d.h>
#include <primitives/worlditem.h>
#include <components/cameracontroller.h>

MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::WindowItem{ parent }
{
    auto scene3D = addItem<Qx::prv::GraphicsScene3D>();
    auto vw0     = scene3D->addView();
    auto cam0    = vw0->camera();
    cam0->reset3DPerspectiveCamera( screen() );
    // cam0->reset3DOrthoCamera( screen(),
    //                          Qx::x_aabb{{-1920, -1080, -1000 },{1920, 1080, 1000}} );


    auto wrldItm = scene3D->addItem<Qx::WorldItem>();
    auto campCpm = wrldItm->attach <Qx::CameraController>();
    campCpm->setCamera( cam0 );
    campCpm->resetControllers();


    auto circleItm = wrldItm->addItem<Circles>();


    // campCpm->setMovement( Qx::CamMoves::PanLeft3D,     "Q" );
    // campCpm->setMovement( Qx::CamMoves::PanRight3D,    "D" );
    // campCpm->setMovement( Qx::CamMoves::PanForward3D,  "Z" );
    // campCpm->setMovement( Qx::CamMoves::PanBackward3D, "S" );

    // campCpm->enableMouse( true );
    // campCpm->setPanSpeed( 1 );
    // campCpm->setZoomSpeed( 3 );
    // campCpm->setRotationSensitivity( 0.001 );



}
