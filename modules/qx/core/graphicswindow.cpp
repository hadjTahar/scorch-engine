#include "graphicswindow.h"
#include "graphicsapp.h"
#include "graphicsscene2d.h"
#include "graphicsscene3d.h"
#include "graphicsitem2d.h"
#include <components/mousecomponent.h>
#include <components/keycomponent.h>


#include <fstream>
#include <execution> // Required for policies

#include <misc/keyevent.h>
#include <misc/mouseevent.h>
#include <misc/platfrom.h>

namespace Qx::prv
{

filament::Engine    *GraphicsWindow::m_filamentEngine   = nullptr;
filament::Renderer  *GraphicsWindow::m_filamentRenderer = nullptr;

GraphicsWindow::GraphicsWindow(CoreItem *parent):
    CoreItem{ parent },
    properties{ *this },
    m_filamentSwapChain{ nullptr },
    m_sdlWindow{ nullptr },
    m_sdlRenderer{ nullptr },
    m_lastPresed{ nullptr },
    m_focusKeyComponent{ nullptr },
    m_sequenceEvent{0,0,0,0}
{
    m_itemType = ItemType::Window;
    dbg_assert( GraphicsApp::app ) << "Invalid app context";
    initWindow();
    dbg_assert( m_sdlWindow ) << "Invalid m_sdlWindow";

    if( !m_filamentEngine )
        m_filamentEngine = filament::Engine::create();

    if( !m_filamentRenderer )
        m_filamentRenderer  = m_filamentEngine->createRenderer();

    dbg_assert( m_filamentEngine )   << "Invalid m_filamentEngine";
    dbg_assert( m_filamentRenderer ) << "Invalid m_filamentRenderer";




    // Set up the clear options
    filament::Renderer::ClearOptions clearOptions;
    clearOptions.clearColor = {0.f, 0.f, 0.f, 1.0f}; // Set to dark grey
    clearOptions.clear = true; // Enable clearing the color buffer
    clearOptions.discard = true; // Optimization: discard contents after use

    m_filamentRenderer->setClearOptions(clearOptions);



    auto nativeWin = Platfrom::nativeWindowHandle(m_sdlWindow);
    m_filamentSwapChain = m_filamentEngine->createSwapChain( nativeWin );
    dbg_assert( m_filamentSwapChain ) << "Invalid m_filamentSwapChain";
}

GraphicsWindow::~GraphicsWindow()
{
    clearChildren();
    m_filamentEngine->destroy( m_filamentSwapChain );
    m_filamentEngine->flushAndWait();
    GraphicsApp::app->windowRemoved( this );

    if( m_sdlRenderer )
        SDL_DestroyRenderer( m_sdlRenderer );

    if( m_sdlWindow )
        SDL_DestroyWindow( m_sdlWindow );
}

x_count GraphicsWindow::windowID() const
{
    const auto ret = static_cast<x_count>(
        SDL_GetWindowID( m_sdlWindow )
        );
    dbg_assert( ret > 0 ) << "Window ID can't be less or equal to zero";
    return ret;
}

void GraphicsWindow::setFullScreen()
{
    SDL_SetWindowFullscreen( m_sdlWindow, true );
}

Screen GraphicsWindow::screen() const
{
    return Screen{ m_sdlWindow };
}

void GraphicsWindow::initWindow()
{
    const int ww = static_cast<int>( 800 );
    const int hh = static_cast<int>( 600 );

    // Create a window
    m_sdlWindow = SDL_CreateWindow(
        "SDL3 Window Example",       // window title
        ww,                          // width
        hh,                          // height
        QX_DEF_SDL_WINDOW_OPTIONS    // window flags
        );

    if( !m_sdlWindow )
        GraphicsApp::app->exit( "SDL_CreateWindow can't create a window" );


    GraphicsApp::app->windowAdded( this );
}

void GraphicsWindow::processComponents(x_real dlt)
{
    const auto res = processComponentsSorted();
    dbg_assert( res ) << "m_processComponents is not sorted";
    processEvents();
    for (auto &cmp : m_processComponents)
        cmp->processComponent( dlt );
}

AppResult GraphicsWindow::processEvents()
{
    if constexpr( QX_DEF_IMMEDIATE_EVENTS )
        return AppResult::CONTINUE;

    for ( auto &evt : m_events)
        handleEvent( &evt );
    m_events.clear();
    return AppResult::CONTINUE;
}

AppResult GraphicsWindow::event(const SDL_Event *const event)
{
    if constexpr( QX_DEF_IMMEDIATE_EVENTS )
        return handleEvent( event );
    else
        m_events.push_back( *event );
    return AppResult::CONTINUE;
}

AppResult GraphicsWindow::handleEvent(const SDL_Event * const event)
{
    const auto evtTp = event->type;
    switch ( evtTp )
    {

    case SDL_EVENT_MOUSE_WHEEL:
    case SDL_EVENT_MOUSE_MOTION:
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        return dispatchMouseEvent( event );
    case SDL_EVENT_KEY_UP:
    case SDL_EVENT_KEY_DOWN:
        return handleKeyEvent( event );
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        sizeChanged();
    case SDL_EVENT_WINDOW_MOVED:
        positionChanged();
        break;
    default:
        break;
    }
    return AppResult::CONTINUE;
}

AppResult GraphicsWindow::dispatchMouseEvent(const SDL_Event * const event)
{
    const auto evtTp = event->type;

    const auto isWheel = (evtTp == SDL_EVENT_MOUSE_WHEEL);
    MouseEvent mEvent{
        event->button.x,
        event->button.y,
        event->button.button,
        event->button.clicks,
        isWheel? event->wheel.x : 0,
        isWheel? event->wheel.y : 0

    };
    const auto &scnItems = childrenView();
    for ( auto &scnItm : scnItems){
        auto scn = castItem<GraphicsScene>( scnItm.get() );
        /// ## Mouse events
        for ( auto &mCmp : m_mouseComponents){
            /// ## ToDo: this solution will only work for one view
            /// ## For multiple view it can call leave earlier
            /// ## when the first view fails the check
            if( !mCmp->checkEvent( mEvent, scn ) ){
                if( mCmp->m_entered && mCmp->move ){
                    mCmp->m_entered = false;
                    mEvent.m_eventType = MouseEventType::MouseLeave;
                    if( mCmp->leave )
                        mCmp->leave( mEvent );
                }
                continue;
            }
            if( handleMouseEvent( event->type, mEvent, mCmp ) )
                return AppResult::CONTINUE;
        }
        if( evtTp != SDL_EVENT_MOUSE_BUTTON_DOWN)
            return AppResult::CONTINUE;

        /// ## Focus events
        for ( auto kCmp : m_keyComponents) {
            if( !kCmp->checkEvent( mEvent, scn ) )
                continue;
            if( updateFocusKeyComponent(kCmp, FocusPolicy::Click) )
                return AppResult::CONTINUE;
        }
    }
    return AppResult::CONTINUE;
}

bool GraphicsWindow::handleMouseEvent(Uint32 evtType,
                                  MouseEvent &mEvent,
                                  MouseComponent *mCmp)
{
    auto accepted = false;
    switch ( evtType )
    {
    case SDL_EVENT_MOUSE_WHEEL:{
        if( mCmp->wheel ){
            mEvent.m_eventType = MouseEventType::MouseWheel;
            accepted = mCmp->wheel( mEvent );
        }
    }

    case SDL_EVENT_MOUSE_MOTION:{
        if( mCmp->move ){
            if( !mCmp->m_entered ){
                mCmp->m_entered = true;
                mEvent.m_eventType = MouseEventType::MouseEnter;
                if( mCmp->enter )
                    accepted = mCmp->enter( mEvent );
            }
            mEvent.m_eventType = MouseEventType::MouseMove;
            accepted = mCmp->move( mEvent );
        }
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_DOWN:{
        m_lastPresed = nullptr;
        /// ## Check mouse components clicks
        m_lastPresed = mCmp;
        if( mCmp->pressed ){
            mEvent.m_eventType = MouseEventType::MousePress;
            accepted = mCmp->pressed( mEvent );
        }
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_UP:{

        if( mCmp->released ){
            mEvent.m_eventType = MouseEventType::MouseRelease;
            accepted = mCmp->released( mEvent );
        }
        if( mCmp == m_lastPresed && mCmp->clicked ){
            mEvent.m_eventType = MouseEventType::MouseClick;
            mCmp->clicked( mEvent );
        }
        break;
    }
    }
    return accepted;
}

bool GraphicsWindow::updateFocusKeyComponent(KeyComponent *kCmp, FocusPolicy policy)
{
    auto accepted = false;
    switch (policy) {
    case FocusPolicy::None:
        return accepted;
    case FocusPolicy::User:
        accepted = kCmp->focusPolicy() != FocusPolicy::None;
        break;
    case FocusPolicy::Click:
        accepted = kCmp->focusPolicy() == FocusPolicy::Click ||
                   kCmp->focusPolicy() == FocusPolicy::Strong ||
                   kCmp->focusPolicy() == FocusPolicy::Wheel;
        break;
    case FocusPolicy::Tab:
        accepted = kCmp->focusPolicy() == FocusPolicy::Tab ||
                   kCmp->focusPolicy() == FocusPolicy::Strong ||
                   kCmp->focusPolicy() == FocusPolicy::Wheel;
        break;
    case FocusPolicy::Strong:
        accepted = kCmp->focusPolicy() == FocusPolicy::Strong ||
                   kCmp->focusPolicy() == FocusPolicy::Wheel;
        break;
    case FocusPolicy::Wheel:
        accepted = kCmp->focusPolicy() == FocusPolicy::Wheel;
    default:
        break;
    }

    if( accepted ){
        if( m_focusKeyComponent )
            m_focusKeyComponent->m_focused = false;
        m_focusKeyComponent = kCmp;
        m_sequenceEvent = {0,0,0,0};
    }
    return accepted;
}

AppResult GraphicsWindow::handleKeyEvent(const SDL_Event * const event)
{
    KeyEvent kEvent{ event->key.key,
                    event->key.mod,
                    event->key.repeat};

    if( kEvent.key() == SDLK_SPACE ){
        removeItem();
    }

    const auto evtTp = event->type;
    switch ( evtTp )
    {
    case SDL_EVENT_KEY_UP:

        m_sequenceEvent.remKey();
        for (auto keyComp : m_keyComponents){
            const auto res = keyComp == m_focusKeyComponent ||
                             keyComp->focusPolicy() == FocusPolicy::Always;
            if( !res )
                continue;
            if( !keyComp->keyReleased )
                continue;
            keyComp->keyReleased(kEvent);
        }
        break;
    case SDL_EVENT_KEY_DOWN:
        m_sequenceEvent.addKey( kEvent.key() );

        for (auto keyComp : m_keyComponents){
            const auto res = keyComp == m_focusKeyComponent ||
                             keyComp->focusPolicy() == FocusPolicy::Always;
            if( !res )
                continue;
            if( keyComp->keyPressed )
                keyComp->keyPressed(kEvent);
            if( m_sequenceEvent.index > 1 && keyComp->sequence )
                keyComp->sequence(m_sequenceEvent);
        }


        break;
    }
    return AppResult::CONTINUE;

}

void GraphicsWindow::updatePropertyStates(MetaItemType sceneType)
{
    dbg_unused( sceneType );
    const auto tp = propertyStates();

    if( has_any( tp, PropertyStates::Geometry ) )
    {
        dbg_assert( m_sdlWindow ) << "Invalid m_sdlWindow";
        const auto newSize = properties.size();
        const auto xx = static_cast<int>( newSize.width );
        const auto yy = static_cast<int>( newSize.height );
        const auto res = SDL_SetWindowSize( m_sdlWindow, xx, yy );
        addPropertyStates(PropertyStates::Transfom |
                          PropertyStates::UpdateChildren );
        if( !res )
            dbg_error() << "Failed to set window position";
    }

    if( has_any( tp, PropertyStates::Transfom ) )
    {
        dbg_assert( m_sdlWindow ) << "Invalid m_sdlWindow";
        const x_vector2 newPos = properties.position();
        const auto xx = static_cast<int>( newPos.x );
        const auto yy = static_cast<int>( newPos.y );
        const auto res = SDL_SetWindowPosition( m_sdlWindow, xx, yy );
        if( !res )
            dbg_error() << "Failed to set window position" ;
    }

    const auto needRender = has_any( tp, PropertyStates::Geometry |
                                            PropertyStates::Transfom |
                                            PropertyStates::Camera );


    if( needRender )
        addPropertyStates( PropertyStates::Render );

}

void GraphicsWindow::positionChanged()
{
    dbg_assert( m_sdlWindow ) << "Invalid m_sdlWindow";
    int xx = 0;
    int yy = 0;
    const auto res = SDL_GetWindowPosition( m_sdlWindow, &xx, &yy );
    if( !res )
        dbg_error() << "Failed to get window position" ;
    properties.setPosition( {xx, yy} );
}

void GraphicsWindow::addCoreComponent(CoreComponent *cmp)
{
    m_processComponents.push_back( cmp );

    std::sort(QX_DEF_PROCESS_COMPONENTS_SORT,
              m_processComponents.begin(),
              m_processComponents.end(),
              sortCmp);
}

void GraphicsWindow::remCoreComponent(CoreComponent *cmp)
{
    const auto res = std::erase(m_processComponents, cmp);
    dbg_assert( res > 0 ) << "Could not remove component";
}

void GraphicsWindow::addMouseComponent(MouseComponent *mCmp)
{
    m_mouseComponents.push_back( mCmp );
    dbg_warning() << "m_mouseComponents is not ordered";
    /// ## ToDo: order m_mouseComponents
    /// ## and re-order m_mouseComponents when Transform changes
}

void GraphicsWindow::remMouseComponent(MouseComponent *mCmp)
{
    const auto res = std::erase(m_mouseComponents, mCmp);
    dbg_assert( res > 0 ) << "Could not remove mouse component";
    if( mCmp == m_lastPresed )
        m_lastPresed = nullptr;
}

void GraphicsWindow::addKeyComponent(KeyComponent *kCmp)
{
    m_keyComponents.push_back( kCmp );
    dbg_warning() << "m_keyComponents is not ordered";
}


void GraphicsWindow::remKeyComponent(KeyComponent *kCmp)
{
    const auto res = std::erase(m_keyComponents, kCmp);
    dbg_assert( res > 0 ) << "Could not remove key component";
    if( kCmp == m_focusKeyComponent )
        m_focusKeyComponent = nullptr;
}

bool GraphicsWindow::processComponentsSorted() const
{
    return std::is_sorted( m_processComponents.begin(), m_processComponents.end(), sortCmp );
}

bool GraphicsWindow::sortCmp(CoreComponent *cmp0, CoreComponent *cmp1)
{
    const auto index0 = cmp0->graphicsItem()->hierarchyIndex();
    const auto index1 = cmp1->graphicsItem()->hierarchyIndex();
    return index0 < index1;
}


filament::Engine *GraphicsWindow::filamentEngine()
{
    return m_filamentEngine;
}

filament::Renderer *GraphicsWindow::filamentRenderer()
{
    return m_filamentRenderer;
}


filament::SwapChain *GraphicsWindow::filamentSwapChain() const
{
    return m_filamentSwapChain;
}

SDL_Window *GraphicsWindow::sdlWindow() const
{
    return m_sdlWindow;
}

SDL_Renderer *GraphicsWindow::sdlRenderer()
{
    if( !m_sdlRenderer ){
        m_sdlRenderer = SDL_CreateRenderer( m_sdlWindow, "" );
        dbg_assert( m_sdlRenderer ) << "Could not create SDL Renderer";
    }

    return m_sdlRenderer;
}


void GraphicsWindow::sizeChanged()
{
    dbg_assert( m_sdlWindow ) << "Invalid m_sdlWindow";
    int ww = 0;
    int hh = 0;
    const auto res = SDL_GetWindowSizeInPixels( m_sdlWindow, &ww, &hh );
    if( !res )
        dbg_error() << "Failed to get window size";
    properties.setSize( { static_cast<x_real>( ww ), static_cast<x_real>( hh )} );


    const auto sz = properties.size();
    const auto &scnItems = childrenView();
    for ( auto &itm : scnItems)
    {
        auto scnItem = prv::CoreItem::castItem<GraphicsItem>( itm.get() );
        scnItem->transform.setSize( sz );
    }

}


}

