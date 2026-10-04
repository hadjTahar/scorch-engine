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

const Qx::x_real sc    = 20;

Qx::x_real tmp( Qx::x_real xx )
{
    /// ## From pixels to physics
    /// ## Add "19_b2_px" something like
    /// ## Or "19_b2m", "19_b2cm"
    return xx / sc;
}

void fixBallDirection(Qx::Box2D::Body* ball)
{
    b2Vec2 v = ball->linearVelocity();

    auto speed = std::sqrt(v.x * v.x + v.y * v.y);

    constexpr auto minSpeed = 80.0f;
    constexpr auto maxSpeed = 85.0f;

    constexpr auto minAngle = 15.0f * 3.14f / 180.0f;

    speed = std::clamp(speed, minSpeed, maxSpeed);

    if (speed < 0.0001f)
    {
        v = { 1.0f, 1.0f };
    }

    float angle = std::atan2(v.y, v.x);

    // Prevent horizontal lock.
    if (std::abs(std::sin(angle)) < std::sin(minAngle))
    {
        float xSign = v.x >= 0.0f ? 1.0f : -1.0f;
        float ySign = v.y >= 0.0f ? 1.0f : -1.0f;

        angle = ySign * minAngle;

        v.x = xSign * std::cos(minAngle);
        v.y = ySign * std::sin(minAngle);
    }

    // Prevent vertical lock.
    constexpr float maxVerticalAngle =
        (90.0f - 15.0f) *  3.14f / 180.0f;

    if (std::abs(std::cos(angle)) < std::sin(minAngle))
    {
        float xSign = v.x >= 0.0f ? 1.0f : -1.0f;
        float ySign = v.y >= 0.0f ? 1.0f : -1.0f;

        v.x = xSign * std::sin(minAngle);
        v.y = ySign * std::cos(minAngle);
    }

    v = b2Normalize(v);
    v *= speed;

    ball->setLinearVelocity(v);
}


MainWindow::MainWindow(CoreItem *parent):
    Qx::prv::GraphicsWindow{ parent }
{

    auto scene = addItem<Qx::prv::GraphicsScene2D<Qx::Backend::CanvasSkiaRasterTexture> >();

    auto vw0   = scene->addView();
    auto cam0  = vw0->camera();

    const auto scrn = screen();
    cam0->reset2DOrthoCamera( scrn );

    cam0->properties.setPosition( {0,0, 0 } );

    vw0->setViewport( {.0, .0, 1., 1.} );
    vw0->setType( Qx::ViewType::Relative );
    vw0->setLogicalSize( scrn.size() );


    auto wrldItm = scene->addItem<Qx::Box2D::WorldItem>();
    auto topItm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    auto botItm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    auto lftItm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();
    auto rhtItm  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();



    auto brickItm0  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();

    auto ballItm = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();

    /// ## This size will be used to scale the world item
    /// ## relative to the window item
    ///
    wrldItm->transform.setSize(
        {
          360,
          640,
          1}
        );
    wrldItm->setWorldAxis( {1,-1,1} );
    wrldItm->world()->setGravity( {0,0} );


    wrldItm->style.setColor( Qx::red() );
    wrldItm->style.setBorderColor( Qx::blue() );
    wrldItm->style.setBorder( 10.f/100.f );

    ballItm->style.setColor( Qx::yellow() );
    ballItm->style.setBorderColor( Qx::green() );
    ballItm->style.setBorder( 2 );


    topItm->style.setColor( Qx::yellow() );
    topItm->style.setBorderColor( Qx::green() );
    topItm->style.setBorder( 2 );

    botItm->style.setColor( Qx::yellow() );
    botItm->style.setBorderColor( Qx::green() );
    botItm->style.setBorder( 2 );


    lftItm->style.setColor( Qx::yellow() );
    lftItm->style.setBorderColor( Qx::green() );
    lftItm->style.setBorder( 2 );

    rhtItm->style.setColor( Qx::yellow() );
    rhtItm->style.setBorderColor( Qx::green() );
    rhtItm->style.setBorder( 2 );


    brickItm0->style.setColor( Qx::yellow() );
    brickItm0->style.setBorderColor( Qx::green() );
    brickItm0->style.setBorder( 2 );


    const Qx::x_real rad   = .5;
    const Qx::x_real pyWW  = tmp(360.f);
    const Qx::x_real pyHH  = tmp(640.f);

    // -------------------------
    // Top floor
    // -------------------------

    topItm->m_body->setType( Qx::Box2D::BodyType::Static );
    auto topItmShp = topItm->m_body->addShape( Qx::Box2D::makeBox( .5*pyWW, .5*pyWW ) );
    topItm->physics.setSize( { pyWW, pyWW, 0});
    topItm->physics.setPosition( {0, pyHH, 0 });
    topItmShp->setDensity( 1, true );
    topItmShp->setRestitution( 1 );

    // -------------------------
    // Bottom floor
    // -------------------------

    botItm->m_body->setType( Qx::Box2D::BodyType::Static );
    auto botItmShp = botItm->m_body->addShape( Qx::Box2D::makeBox( .5*pyWW, .5*pyWW ) );
    botItm->physics.setSize( { pyWW, pyWW, 0});
    botItm->physics.setPosition( {0, -pyWW, 0 });
    botItmShp->setDensity( 1, true );
    botItmShp->setRestitution( 1 );


    // -------------------------
    // Left floor
    // -------------------------

    lftItm->m_body->setType( Qx::Box2D::BodyType::Static );
    auto lftItmShp = lftItm->m_body->addShape( Qx::Box2D::makeBox( .5*pyHH, .5*pyHH ) );
    lftItm->physics.setSize( { pyHH, pyHH, 0});
    lftItm->physics.setPosition( {-pyHH, 0, 0 });
    lftItmShp->setDensity( 1, true );
    lftItmShp->setRestitution( 1 );

    // -------------------------
    // Right floor
    // -------------------------

    rhtItm->m_body->setType( Qx::Box2D::BodyType::Static );
    auto rhtItmShp = rhtItm->m_body->addShape( Qx::Box2D::makeBox( .5*pyHH, .5*pyHH ) );
    rhtItm->physics.setSize( { pyHH, pyHH, 0});
    rhtItm->physics.setPosition( {pyWW, 0, 0 });
    rhtItmShp->setDensity( 1, true );
    rhtItmShp->setRestitution( 1 );


    // -------------------------
    // Create ball
    // -------------------------


    ballItm->physics.setSize( { 2*rad, 2*rad, 0});
    auto ballBody = ballItm->m_body;

    ballBody->setPosition( {2, 1.5f} );
    ballBody->setType( Qx::Box2D::BodyType::Dynamic );
    ballBody->setLinearVelocity( {30.0f, 80.0f} );

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


    // -------------------------
    // Brick 0
    // -------------------------

    const Qx::x_real ww  = 20.f / sc;
    const Qx::x_real hh  = 10.f / sc;
    const Qx::x_real xx  = 150.f / sc;
    const Qx::x_real yy  = 200.f / sc;


    brickItm0->m_body->setType( Qx::Box2D::BodyType::Static );
    auto brickItm0Shp = brickItm0->m_body->addShape( Qx::Box2D::makeBox( .5*ww, .5*hh ) );
    brickItm0->physics.setSize( { ww, hh, 0});
    brickItm0->physics.setPosition( {xx, yy, 0 });
    brickItm0Shp->setDensity( 1, true );
    brickItm0Shp->setRestitution( .7 );


    wrldItm->step = [ballItm]()
    {
        auto ball = ballItm->m_body;
        fixBallDirection( ball );
        // dbg_print_st() << xv.x << " : " << xv.y;
    };

}
