#include "mainwindow.h"

#include <items/rectangle.h>
#include <core/graphicsitem2d.h>
#include <core/graphicsscene2d.h>
#include <backends/canvassdlrenderer.h>
#include <backends/canvasskiarastersurface.h>
#include <backends/canvasskiarastertexture.h>
#include <backends/canvasskiaopenglsurface.h>
#include <backends/canvasskiaopengltexture.h>


#include <physics/bodyitem.h>
#include <physics/worlditem.h>



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


    auto wrldItm  = scene->addItem<Qx::Box2D::WorldItem>();
    auto ballItm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    auto flr0Itm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    // auto flr1Itm  = wrldItm->addBodyItem<Qx::Rectangle>();

    wrldItm->transform.setScale( {50,-50, 1} );
    auto world0 = wrldItm->world();


    wrldItm->style.setColor( Qx::red() );
    wrldItm->style.setBorderColor( Qx::transparent() );
    wrldItm->style.setBorder( 0 );

    ballItm->style.setColor( Qx::yellow() );
    ballItm->style.setBorderColor( Qx::transparent() );
    ballItm->style.setBorder( 0 );


    flr0Itm->style.setColor( Qx::yellow() );
    flr0Itm->style.setBorderColor( Qx::transparent() );
    flr0Itm->style.setBorder( 0 );


    // flr1Itm->style.setColor( Qx::yellow() );
    // flr1Itm->style.setBorderColor( Qx::transparent() );
    // flr1Itm->style.setBorder( 0 );



    // -------------------------
    // Create floor
    // -------------------------

    auto floor0 = world0->addBody();
    floor0->setPosition( {0.0f, 5+5.0f} );
    floor0->setType( Qx::Box2D::BodyType::Static );
    auto floorShp0 = floor0->addShape( Qx::Box2D::makeBox(5,5) );
    floorShp0->setDensity( 1, true );
    floorShp0->setRestitution( .7 );


    flr0Itm->transform.setPosition( {
        0,
        5,
        0
    });
    flr0Itm->transform.setSize( { 5, .5, 0});


    // -------------------------
    // Create floor
    // -------------------------

    auto floor1 = world0->addBody();
    floor1->setPosition( {0.0f, -5.0f} );
    floor1->setType( Qx::Box2D::BodyType::Static );
    auto floorShp1 = floor1->addShape( Qx::Box2D::makeBox(5,5) );
    floorShp1->setDensity( 1, true );
    floorShp1->setRestitution( .7 );


    // -------------------------
    // Create ball
    // -------------------------
    const Qx::x_real rad = .5;


    auto ball = world0->addBody();
    ball->setPosition( {rad, 1.5f} );
    ball->setType( Qx::Box2D::BodyType::Dynamic );
    ball->setLinearVelocity( {.0f, 15.0f} );

    /// ## --------------------------------------------------

    // auto polygon = Qx::Box2D::makeBox( rad , rad);
    // polygon.centroid = { rad, rad };
    // auto ballShp = ball->addShape( polygon );
    // ballShp->setDensity( 1, true );
    // ballShp->setRestitution( .7 );

    /// ## --------------------------------------------------


    Qx::Box2D::Circle circle;
    circle.center = { 0, 0 };
    circle.radius = rad;
    auto ballShp = ball->addShape( circle );
    ballShp->setDensity( 1.0f, true );
    ballShp->setRestitution( 1 );



    wrldItm->step = [ball, ballItm, rad]()
    {
        const auto position = ball->position();
        dbg_print_st() << position.x << " : " << position.y;

        ballItm->transform.setPosition( {
            position.x - rad,
            position.y - rad,
            0
        });


        ballItm->transform.setSize( { 2*rad, 2*rad, 0});

    };
}
