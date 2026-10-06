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



    // auto brickItm0  = wrldItm->addBodyItem<Qx::Box2D::BodyItem>();

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
    wrldItm->setWorldAxis( {1,1,1} );
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



    const Qx::x_real sc     = 20;
    const Qx::x_real rad    = 10;
    const Qx::x_real pyWW   = 360.f;
    const Qx::x_real pyHH   = 640.f;
    const Qx::x_real wallSz = 10.f;

    // -------------------------
    // Top floor
    // -------------------------

    topItm->m_body->setType( Qx::Box2D::BodyType::Static );
    topItm->physics.setSize( { pyWW, wallSz, 0});
    topItm->physics.setPosition( {0, pyHH, 0 });
    auto topItmShp = topItm->m_body->addShape( topItm->makeBox( pyWW, wallSz ) );
    topItmShp->setDensity( 1, true );
    topItmShp->setRestitution( 1 );

    // -------------------------
    // Bottom floor
    // -------------------------

    botItm->m_body->setType( Qx::Box2D::BodyType::Static );
    botItm->physics.setSize( { pyWW, wallSz, 0});
    botItm->physics.setPosition( {0, -wallSz, 0 });
    auto botItmShp = botItm->m_body->addShape( botItm->makeBox( pyWW, wallSz ) );
    botItmShp->setDensity( 1, true );
    botItmShp->setRestitution( 1 );




    // -------------------------
    // Create ball
    // -------------------------


    ballItm->physics.setSize( { 2*rad, 2*rad, 0});
    auto ballBody = ballItm->m_body;

    ballBody->setPosition( {2, 1.5f} );
    ballBody->setType( Qx::Box2D::BodyType::Dynamic );
    ballBody->setLinearVelocity( {0.0f, 80.0f} );

    /// ## --------------------------------------------------

    // auto polygon = ballItm->makeBox( rad , rad);
    // // polygon.centroid = { rad, rad };
    // auto ballShp = ballBody->addShape( polygon );
    // ballShp->setDensity( 1, true );
    // ballShp->setRestitution( .7 );

    /// ## --------------------------------------------------

    Qx::Box2D::Circle circle = ballItm->makeCircle( rad );
    auto ballShp = ballBody->addShape( circle );
    ballShp->setDensity( 1.0f, true );
    ballShp->setRestitution( 1 );




}
