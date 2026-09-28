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

    const auto scrn = screen();
    cam0->reset2DOrthoCamera( scrn );

    vw0->setViewport( {.0, .0, 1., 1.} );
    vw0->setType( Qx::ViewType::Relative );
    vw0->setLogicalSize( scrn.size() );


    auto wrldItm  = scene->addItem<Qx::Box2D::WorldItem>();
    auto flr0Itm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    auto flr1Itm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    auto ballItm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    // auto flr1Itm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();

    /// ## This size will be used to scale the world item
    /// ## relative to the window item
    ///
    wrldItm->transform.setSize(
        {
          360,
          640,
          1}
        );
    wrldItm->setWorldAxis( {1,1,1} );
    auto world0 = wrldItm->world();



    wrldItm->style.setColor( Qx::red() );
    wrldItm->style.setBorderColor( Qx::blue() );
    wrldItm->style.setBorder( 10.f/100.f );

    ballItm->style.setColor( Qx::yellow() );
    ballItm->style.setBorderColor( Qx::transparent() );
    ballItm->style.setBorder( 0 );


    flr0Itm->style.setColor( Qx::yellow() );
    flr0Itm->style.setBorderColor( Qx::transparent() );
    flr0Itm->style.setBorder( 0 );


    flr1Itm->style.setColor( Qx::yellow() );
    flr1Itm->style.setBorderColor( Qx::transparent() );
    flr1Itm->style.setBorder( 0 );


    const Qx::x_real rad    = .5;
    const Qx::x_real flrSz  = 5;

    // -------------------------
    // Top floor
    // -------------------------

    flr0Itm->m_body->setType( Qx::Box2D::BodyType::Static );
    auto floorShp0 = flr0Itm->m_body->addShape( Qx::Box2D::makeBox( .5*flrSz, .5*flrSz ) );
    flr0Itm->physics.setSize( { flrSz, flrSz, 0});
    flr0Itm->physics.setPosition( {0, 20, 0 });
    floorShp0->setDensity( 1, true );
    floorShp0->setRestitution( .7 );

    // -------------------------
    // Bottom floor
    // -------------------------

    flr1Itm->m_body->setType( Qx::Box2D::BodyType::Static );
    auto floorShp1 = flr1Itm->m_body->addShape( Qx::Box2D::makeBox( .5*flrSz, .5*flrSz ) );
    flr1Itm->physics.setSize( { flrSz, flrSz, 0});
    flr1Itm->physics.setPosition( {0, -flrSz, 0 });
    floorShp1->setDensity( 1, true );
    floorShp1->setRestitution( .7 );


    // -------------------------
    // Create ball
    // -------------------------


    ballItm->physics.setSize( { 2*rad, 2*rad, 0});
    auto ballBody = ballItm->m_body;

    ballBody->setPosition( {2, 1.5f} );
    ballBody->setType( Qx::Box2D::BodyType::Dynamic );
    ballBody->setLinearVelocity( {.0f, 80.0f} );

    /// ## --------------------------------------------------

    // auto polygon = Qx::Box2D::makeBox( rad , rad);
    // // polygon.centroid = { rad, rad };
    // auto ballShp = ballBody->addShape( polygon );
    // ballShp->setDensity( 1, true );
    // ballShp->setRestitution( .7 );

    /// ## --------------------------------------------------

    Qx::Box2D::Circle circle;
    circle.center = { 0, 0};
    circle.radius = rad;
    auto ballShp = ballBody->addShape( circle );
    ballShp->setDensity( 1.0f, true );
    ballShp->setRestitution( 1 );

    return;

    wrldItm->step = [ballBody, ballItm, rad]()
    {
        const auto position = ballBody->position();
        dbg_print_st() << position.x << " : " << position.y;

    };
}
