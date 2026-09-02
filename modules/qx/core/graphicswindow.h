#ifndef GRAPHICSWINDOW_H
#define GRAPHICSWINDOW_H

#include "coreitem.h"
#include "properties/properties.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>

#include <misc/sequenceevent.h>
#include <misc/screen.h>

namespace Qx
{
class MouseComponent;
class KeyComponent;
}

namespace Qx::prv
{

class GraphicsWindow : public prv::CoreItem
{
    friend class GraphicsApp;
    friend class CoreComponent;
    friend class Qx::MouseComponent;
    friend class Qx::KeyComponent;
    friend class RenderBackendBase;

    // friend class GraphicsScene2D;

    QX_META_OBJECT( GraphicsWindow,
                   MetaItemType::Window,
                   MetaItemType::GraphicsScene2D|MetaItemType::GraphicsScene3D )

public:
    WindowProperties properties;

public:
    GraphicsWindow(CoreItem *parent);
    ~GraphicsWindow();
    x_count windowID() const;
    void setFullScreen();
    Screen screen() const;

    SDL_Window   *sdlWindow() const;
    SDL_Renderer *sdlRenderer();


protected:
    void initWindow();
    void processComponents(x_real dlt);
    void render(Canvas*)override final{dbg_assert(false) << "GraphicsWindow::render should never be called";}
    void updateModel( GraphicsMeshModel * )override final{dbg_assert(false) << "GraphicsWindow::render should never be called";}
    inline AppResult processEvents();
    AppResult event(const SDL_Event * const event);
    AppResult handleEvent(const SDL_Event * const event);
    AppResult dispatchMouseEvent(const SDL_Event * const event);
    bool handleMouseEvent(Uint32 evtType,
                          MouseEvent &mEvent,
                          MouseComponent *mCmp);
    bool updateFocusKeyComponent(KeyComponent *kCmp, FocusPolicy policy);
    AppResult handleKeyEvent(const SDL_Event * const event);
    void updatePropertyStates(MetaItemType sceneType)override final;

private:
    void sizeChanged();
    void positionChanged();

    void addCoreComponent(CoreComponent *cmp);
    void remCoreComponent(CoreComponent *cmp);
    void addMouseComponent(MouseComponent *mCmp);
    void remMouseComponent(MouseComponent *mCmp);
    void addKeyComponent(KeyComponent *kCmp);
    void remKeyComponent(KeyComponent *kCmp);
    bool processComponentsSorted() const;

    static bool sortCmp(CoreComponent *cmp0, CoreComponent *cmp1);

private:

    void              *m_filamentBackendSwapChain;

    SDL_Window        *m_sdlWindow;
    SDL_Renderer      *m_sdlRenderer;
    MouseComponent    *m_lastPresed;
    KeyComponent      *m_focusKeyComponent;
    SequenceEvent      m_sequenceEvent;
    std::vector< SDL_Event> m_events;
    std::vector<CoreComponent*>   m_processComponents;
    std::vector<MouseComponent*>  m_mouseComponents;
    std::vector<KeyComponent*>    m_keyComponents;
};

}
#endif // GRAPHICSWINDOW_H
