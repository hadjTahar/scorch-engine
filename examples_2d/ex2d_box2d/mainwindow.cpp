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



int test()
{
    // Create physics world with gravity.
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, -9.8f};
    // worldDef.restitution = 1.0f;

    b2CreateWorld(&worldDef);
    b2WorldId world = b2CreateWorld(&worldDef);

    // -------------------------
    // Create floor
    // -------------------------

    b2BodyDef floorDef = b2DefaultBodyDef();
    floorDef.position = {0.0f, -5.0f};

    b2BodyId floor = b2CreateBody(world, &floorDef);

    b2Polygon floorShape = b2MakeBox(10.0f, 0.5f);

    b2ShapeDef floorShapeDef = b2DefaultShapeDef();

    b2CreatePolygonShape(
        floor,
        &floorShapeDef,
        &floorShape
        );

    // -------------------------
    // Create ball
    // -------------------------

    b2BodyDef ballDef = b2DefaultBodyDef();
    ballDef.type = b2_dynamicBody;
    ballDef.position = {0.0f, 5.0f};

    b2BodyId ball = b2CreateBody(world, &ballDef);

    b2Circle circle;
    circle.center = {0.0f, 0.0f};
    circle.radius = 0.5f;

    b2ShapeDef ballShapeDef = b2DefaultShapeDef();
    ballShapeDef.density = 1.0f;
    // ballShapeDef.restitution = 1.0f;

    b2CreateCircleShape(
        ball,
        &ballShapeDef,
        &circle
        );

    // Give ball an initial velocity.
    b2Body_SetLinearVelocity(ball, {3.0f, -5.0f});

    // -------------------------
    // Simulation
    // -------------------------

    constexpr float timeStep = 1.0f / 60.0f;

    for (int frame = 0; frame < 300; ++frame)
    {
        b2World_Step(world, timeStep, 4);

        b2Vec2 position = b2Body_GetPosition(ball);
        b2Vec2 velocity = b2Body_GetLinearVelocity(ball);

        std::cout
            << "Position: "
            << position.x << ", "
            << position.y
            << "  Velocity: "
            << velocity.x << ", "
            << velocity.y
            << '\n';
    }

    b2DestroyWorld(world);

    return 0;
}

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
    itm1->style.setColor( Qx::green() );

    // test();

    auto box2DCmp = itm0->attach<Qx::Box2D::PhysicsComponent>();


    Qx::Box2D::WorldOpts worldOpts;
    worldOpts.gravity = {0.0f, -9.8f};
    auto world0 = box2DCmp->createWorld( worldOpts );




    // -------------------------
    // Create floor
    // --------------

    Qx::Box2D::BodyOpts floorOpts;
    floorOpts.position = {0.0f, -5.0f};


    Qx::Box2D::Body floor(world0);
    auto floorShape = box2DCmp->makeBox(10.0f, 0.5f);
    Qx::Box2D::ShapeOpts floorShapeOpts;

    box2DCmp->createPolygonShape(
        floor,
        floorShapeOpts,
        floorShape
        );

    // -------------------------
    // Create ball
    // -------------------------


    Qx::Box2D::Body ball(world0);
    ball.setPosition( {0.0f, 5.0f} );
    ball.setType( b2_dynamicBody );

    Qx::Box2D::Circle circle;
    circle.center = {0.0f, 0.0f};
    circle.radius = 0.5f;

    Qx::Box2D::ShapeOpts ballShapeDef;
    ballShapeDef.density = 1.0f;
    // ballShapeDef.restitution = 1.0f;

    box2DCmp->createCircleShape(
        ball,
        ballShapeDef,
        circle
        );

    // Give ball an initial velocity.
    ball.setLinearVelocity( {3.0f, -5.0f} );


    box2DCmp->step = [ball]()
    {
        // b2Vec2 position = b2Body_GetPosition(ball);
        // b2Vec2 velocity = b2Body_GetLinearVelocity(ball);

        // std::cout
        //     << "Position: "
        //     << position.x << ", "
        //     << position.y
        //     << "  Velocity: "
        //     << velocity.x << ", "
        //     << velocity.y
        //     << '\n';
    };
}
