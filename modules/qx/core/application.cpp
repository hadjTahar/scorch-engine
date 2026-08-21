#include "application.h"
#include "graphicsscene.h"
#include <timers/timerbase.h>
#include <timers/timercallback.h>
#include <timers/timersprobe.h>


namespace Qx::prv
{

Application *Application::app = nullptr;


Application::Application(x_real pps, x_real fpsHint):
    RootBaseItem{},
    m_exiting{ false }
{
    dbg_assert( !app ) << "Only one app can be created";
    if( app )
        exit( "Only one app can be created" );
    app = this;
    const auto res = SDL_Init( QX_DEF_SDL_INIT_OPTIONS );
    dbg_assert( res ) << "Cant init SDL";

    dbg_assert( pps >= fpsHint )<< "FPS must be greater than or equal to PPS";
    TimerBase::initTimer( fpsHint );

    TimerLoop::init( pps, fpsHint );
    m_delayLoop.fixedDltMS      = 1000.f / pps;
    m_delayLoop.loopsPerFrame   = 1;
    m_delayLoop.delayPerFrameMS = static_cast<x_time>(1000) / fpsHint;
    m_delayLoop.fixedDltTicks   = 0;
}

Application::~Application()
{
    m_exiting = true;
    TimerCallback::clearSingleShots();
    clearChildren();    
    CoreItem::stepPendings();
    TimerBase::clearTimers();

    WindowItem::m_filamentEngine->flushAndWait();
    WindowItem::m_filamentEngine->destroy(WindowItem::m_filamentRenderer);
    filament::Engine::destroy(WindowItem::m_filamentEngine);

}

void Application::exit(const std::string &reason)
{
    m_exiting = true;
    if( !reason.empty() )
        dbg_print() << "Exiting, because : " << reason;
    SDL_Event event{};
    event.type = SDL_EVENT_QUIT;
    SDL_PushEvent( &event );
}


AppResult Application::init(void **appstate, int argc, char *argv[])
{
    dbg_unused(appstate);
    dbg_unused(argc);
    dbg_unused(argv);
    /// ## Add nodes like windows, before SDL::iterate
    /// ## so the app won't exit
    ///
    CoreItem::stepPendings();
    return AppResult::CONTINUE;
}

AppResult Application::iterate(void *appstate)
{
    dbg_unused(appstate);
    TimerBase::startFrame();
    TimersProbe::startProbe();
    const auto dropFrame = QX_DEF_DROP_FRAME_DELAY > 0 && m_delayLoop.delayPerFrameMS < QX_DEF_DROP_FRAME_DELAY;
    updateChildren( dropFrame );
    TimerBase::endUpdates();
    SDL_Delay( static_cast<Uint32>( m_delayLoop.delayPerFrameMS ) );

    m_delayLoop = TimerLoop::delayLoop();
    TimersProbe::endProbe( m_delayLoop.loopsPerFrame, m_delayLoop.delayPerFrameMS );
    return AppResult::CONTINUE;
}

AppResult Application::event(void *appstate, SDL_Event *event)
{
    dbg_unused( appstate );
    if( childrenView().empty() )
        exit();
    const auto eventTp = event->type;
    switch ( eventTp ) {
    case SDL_EVENT_QUIT:
        return AppResult::SUCCESS;
        break;
    default:
        break;
    }

    handleEvent( event );
    return AppResult::CONTINUE;
}

void Application::quit(void *appstate, AppResult result)
{

    dbg_unused( appstate );
    dbg_unused( result );
    CoreItem::stepPendings();
}


void Application::handleEvent( const SDL_Event *const event)
{
    const auto winID = static_cast<x_count>( event->window.windowID );
    auto wind = window( winID );
    if( !winID )
        return;

    const auto eventTp = event->type;
    switch ( eventTp )
    {
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        if( wind )
            wind->removeItem();
        break;
    case SDL_EVENT_WINDOW_DESTROYED:
        break;
    default:
        if( wind )
            wind->event( event );
        break;
    }
}

void Application::windowAdded(WindowItem *wind)
{
    m_windows[ wind->windowID() ] = wind;
}

void Application::windowRemoved(WindowItem *wind)
{
    const auto winID = static_cast<x_count>( wind->windowID() );
    const auto cnt  = m_windows.erase( winID );
    dbg_assert( cnt == 1 ) << "Expected cnt to be 1, " << "instead got " << cnt;
}

void Application::updateChildren(bool dropFrame)
{
    meta_check_hierarchy();
    /// ## [1] : update items per window->views
    ///
    for (x_count idx = 0; idx < m_delayLoop.loopsPerFrame; ++idx)
    {
        if( m_exiting )
            break;
        TimerBase::stepTimers(m_delayLoop.fixedDltTicks);
        const auto dltMS = static_cast<x_real>( m_delayLoop.fixedDltMS );
        const auto &winds = childrenView();

        dbg_assert( m_windows.size() == winds.size() ) << "Sizes must be equal";
        for ( auto &[idx,win] : m_windows)
        {
            TimersProbe::disp( win->sdlWindow() );
            if( m_exiting )
                break;
            win->processComponents( dltMS );
            auto &views = win->childrenView();
            for ( const auto &vw : views)
            {
                if( m_exiting )
                    break;
                auto gVw = vw.get();
                gVw->updateItem( gVw->meta_item_type() );
            }
        }
    }


    renderToBackend( dropFrame );
    CoreItem::stepPendings();
}

void Application::renderToBackend(bool dropFrame)
{
    if( dropFrame )
    {
        dbg_warning() << "Frame dropped";
        return;
    }

    for ( auto &[idx,win] : m_windows)
    {
        win->updatePropertyStates( MetaItemType::None );
        const auto winPropertyTp = win->propertyStates();
        const auto rndr = has_any( winPropertyTp, PropertyStates::Render );
        if( !rndr )
            continue;
        auto &views = win->childrenView();

        for ( auto &vw : views)
        {
            const auto sz = win->properties.size();
            auto graphicsScn = castItem<GraphicsScene>( vw.get() );
            graphicsScn->initCanvas( win );
            graphicsScn->renderViews( win );
            graphicsScn->resetPropertyStates();
        }
        win->resetPropertyStates();
    }

    resetPropertyStates();
}

WindowItem *Application::window(x_count idx)
{
    if( m_windows.contains( idx ) )
        return m_windows[ idx ];
    return nullptr;
}



}
