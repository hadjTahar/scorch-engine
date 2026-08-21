#include <misc/utils/xunits.h>
#include "mainwindow.h"

#include <misc/events/mouseevent.h>
#include <misc/types/assets.h>
#include <misc/ui/uidevice.h>
#include <core/managers/g2dgraphicsmanager.h>
#include <ui/base/uirectanglenode.h>
#include <components/essentials/glkeycomponent.h>
#include <components/essentials/glmousecomponent.h>
#include <components/essentials/glnodeobservercomponent.h>
#include <components/essentials/glpetrinetcomponent.h>
#include <components/behaviors/glmoveanimation.h>
#include <g2d/primitives/g2dcameracontrolnode.h>


MainWindow::MainWindow():
    UIWindow{}
{
    /// ## Leave this empty. Use "::setup" instead
}

void MainWindow::setup()
{
    auto g2dMngr = addGraphicsManager<Qx::G2DGraphicsManager>( false );
    g2dMngr->setRenderPolicy( Qx::RenderPolicy::StatefulRender );
    auto vwport0 = g2dMngr->addViewport();
    // vwport0->setFixedViewRect( .0_px, .0_px, 500_px, 500_px );
    vwport0->setShowRect( true );
    vwport0->setClip( true );
    vwport0->setVisible( true );

    auto cam0 = vwport0->camera();
    cam0->setViewSize( 800_dp, 800_dp );
    auto camNode0 = g2dMngr->addNode<Qx::G2DCameraControlNode>();
    camNode0->setCamera( cam0 );
    // cam0->setPosition( dp( -250 ), dp( -250 ) );
    cam0->setFocalLength( 33.2f );

    auto nd = g2dMngr->addNode<Qx::UIRectangleNode>();

    auto petriComp = Qx::addComponent<Qx::GLPetriNetComponent>( nd );

    petriComp->tokensChanged = []( ptn::PetriPlace *plc, int tkns)
    {
        if( tkns == 0 )
            return;
        qx_debug() << plc << " : " <<
            plc->index() << " : " <<
            tkns;
    };

    auto petriEngine = petriComp->petriEngine();
    petriEngine->setSize( 3, 1 );

    auto p0 = petriEngine->addPlace();
    auto p1 = petriEngine->addTimerPlace();
    // auto p1 = petriEngine->addDelayedPlace();
    // auto p1 = petriEngine->addStochasticPlace();
    // p1->setRatePerSecond( .001 );


    auto p2 = petriEngine->addPlace();

    auto t0 = petriEngine->addTransition();
    // auto t1 = petriEngine->addTransition();

    t0->linkIn( p0, 1 );
    t0->linkIn( p1, 1 );
    t0->linkOut( p2, 1 );

    p0->addTokens( 11 );
    p1->addTokens( 7 );

}




