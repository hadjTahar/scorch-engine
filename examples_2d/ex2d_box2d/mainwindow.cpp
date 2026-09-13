#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvassdlrenderer.h>
#include <backends/canvasskiarastersurface.h>
#include <backends/canvasskiarastertexture.h>
#include <backends/canvasskiaopenglsurface.h>
#include <backends/canvasskiaopengltexture.h>


#include <physics/box2dworlditem.h>
#include <physics/physicscomponent.h>



MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterTexture> >();

    auto vw0   = scene->addView();
    auto cam0  = vw0->camera();
    cam0->reset2DOrthoCamera( screen() );



    vw0->setViewport( {.0, .0, 1, 1 } );
    vw0->setType( Qx::ViewType::Relative );
    vw0->setLogicalSize( {1920,1080} );


    auto itm0     = scene->addItem<Qx::Box2D::WorldItem>();
    auto ballItm  = itm0->addItem<Qx::Rectangle>();
    auto flr0Itm  = itm0->addItem<Qx::Rectangle>();
    // auto flr1Itm  = itm0->addItem<Qx::Rectangle>();

    itm0->transform.setScale( {50,-50, 1} );


    itm0->style.setColor( Qx::red() );
    itm0->style.setBorderColor( Qx::transparent() );
    itm0->style.setBorder( 0 );

    ballItm->style.setColor( Qx::yellow() );
    ballItm->style.setBorderColor( Qx::transparent() );
    ballItm->style.setBorder( 0 );


    flr0Itm->style.setColor( Qx::yellow() );
    flr0Itm->style.setBorderColor( Qx::transparent() );
    flr0Itm->style.setBorder( 0 );


    // flr1Itm->style.setColor( Qx::yellow() );
    // flr1Itm->style.setBorderColor( Qx::transparent() );
    // flr1Itm->style.setBorder( 0 );







    auto box2DCmp = itm0->attach<Qx::Box2D::PhysicsComponent>();
    auto world0 = box2DCmp->createWorld();
    // world0->setGravity( {0.0f, -9.8f} );

    // -------------------------
    // Create floor
    // -------------------------

    auto floor0 = world0->addBody();
    floor0->setPosition( {0.0f, 5+5.0f} );
    floor0->setType( b2_staticBody );
    auto floorShp0 = floor0->addShape( b2MakeBox(5,5) );
    floorShp0->setDensity( 1, true );
    floorShp0->setRestitution( .7 );


    flr0Itm->transform.setPosition( {
        0 + .05,
        5 + .05,
        0
    });
    flr0Itm->transform.setSize( { 5, .5, 0});


    // -------------------------
    // Create floor
    // -------------------------

    auto floor1 = world0->addBody();
    floor1->setPosition( {0.0f, -5.0f} );
    floor1->setType( b2_staticBody );
    auto floorShp1 = floor1->addShape( b2MakeBox(5,5) );
    floorShp1->setDensity( 1, true );
    floorShp1->setRestitution( .7 );


    // -------------------------
    // Create ball
    // -------------------------
    const Qx::x_real rad = .5;


    auto ball = world0->addBody();
    ball->setPosition( {rad, 1.5f} );
    ball->setType( b2_dynamicBody );
    ball->setLinearVelocity( {.0f, 15.0f} );

    /// ## --------------------------------------------------

    auto polygon = b2MakeBox( rad , rad);
    polygon.centroid = { rad, rad };
    auto ballShp = ball->addShape( polygon );
    ballShp->setDensity( 1, true );
    ballShp->setRestitution( .7 );

    /// ## --------------------------------------------------


    // Qx::Box2D::Circle circle;
    // circle.center = { 0, 0 };
    // circle.radius = rad;
    // auto ballShp = ball->addShape( circle );
    // ballShp->setDensity( 1.0f, true );
    // ballShp->setRestitution( 1 );



    box2DCmp->step = [ball, ballItm, rad]()
    {
        b2Vec2 position = ball->position();
        dbg_print_st() << position.x << " : " << position.y;

        ballItm->transform.setPosition( {
            position.x - rad + .05,
            position.y - rad + .05,
            0
        });


        ballItm->transform.setSize( { 2*rad, 2*rad, 0});

    };
}
