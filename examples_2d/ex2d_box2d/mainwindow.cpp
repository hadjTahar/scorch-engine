#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvassdlrenderer.h>
#include <backends/canvasskiarastersurface.h>
#include <backends/canvasskiarastertexture.h>
#include <backends/canvasskiaopenglsurface.h>
#include <backends/canvasskiaopengltexture.h>


#include <physics/physicscomponent.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterTexture> >();

    auto vw0   = scene->addView();
    auto cam0  = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );
    auto itm0  = scene->addItem<Qx::Rectangle>();
    auto itm1  = itm0->addItem<Qx::Rectangle>();


    itm0->transform.setPosition( {100, 100, 0 } );
    itm0->style.setColor( Qx::red() );

    itm1->transform.setPosition( {20, 20, 0 } );
    itm1->transform.setSize( {20, 20, 0 } );
    itm1->style.setColor( Qx::green() );

    auto box2DCmp = itm0->attach<Qx::Box2D::PhysicsComponent>();
    auto world0 = box2DCmp->createWorld();
    world0->setGravity( {0.0f, -9.8f} );

    // -------------------------
    // Create floor
    // -------------------------

    auto floor0 = world0->addBody();
    floor0->setPosition( {0.0f, -220.0f} );
    auto floorShp0 = floor0->addShape( b2MakeBox(5,5) );
    floorShp0->setDensity( 1, true );
    floorShp0->setRestitution( .1 );


    // -------------------------
    // Create floor
    // -------------------------

    auto floor1 = world0->addBody();
    floor1->setPosition( {0.0f, 20.0f} );
    auto floorShp1 = floor1->addShape( b2MakeBox(5,5) );
    floorShp1->setDensity( 1, true );
    floorShp1->setRestitution( .1 );


    // -------------------------
    // Create ball
    // -------------------------


    auto ball = world0->addBody();
    ball->setPosition( {0.0f, 15.0f} );
    ball->setType( b2_dynamicBody );

    Qx::Box2D::Circle circle;
    circle.center = {0.0f, 0.0f};
    circle.radius = 0.5f;
    auto ballShp = ball->addShape( circle );
    ballShp->setDensity( 1.0f, true );
    ballShp->setRestitution( 1 );



    // Give ball an initial velocity.
    ball->setLinearVelocity( {.0f, -1225.0f} );


    box2DCmp->step = [ball, itm1]()
    {
        b2Vec2 position = ball->position();

        itm1->transform.setPosition( {position.x, -position.y, 0 });

    };
}
