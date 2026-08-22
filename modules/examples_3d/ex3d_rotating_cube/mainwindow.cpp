#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene3d.h>
#include <primitives/cube.h>
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


    auto cubeItm = wrldItm->addItem<Qx::Cube>();
    auto rotationCpm = wrldItm->attach <Qx::prv::CoreComponent>();

    cubeItm->transform.setPosition({100,100,100});

    Qx::x_pivot pvPt{ Qx::PivotType::BoundingSize,
                        Qx::PivotAxis::Mid,
                        Qx::PivotAxis::Mid,
                        Qx::PivotAxis::Mid};

    cubeItm->transform.setPivot( pvPt );


    rotationCpm->process = [cubeItm](Qx::x_real dlt)
    {
        // auto pos = cubeItm->transform.position();
        // pos += (dlt/1000.f) * Qx::x_vector3{3,3,3};
        // cubeItm->transform.setPosition( pos );


        auto& transform = cubeItm->transform;

        const float rotationSpeed = glm::radians( 30.0f);
        const float deltaTime = dlt / 1000.0f;
        const float angle = rotationSpeed * deltaTime;

        const glm::vec3 axis(.0f, .0f, 1.0f);
        const glm::quat deltaRotation = glm::angleAxis(angle, axis);

        // The actual center of the cube
        const glm::vec3 center = {5,5,5};

        // Current position

        // Rotate position around center
        // position = center + deltaRotation * (position - center);

        // Rotate the cube itself
        glm::quat rotation = transform.rotation();
        rotation = deltaRotation * rotation;
        rotation = glm::normalize(rotation);

        // Apply
        transform.setRotation(rotation);

    };





}
