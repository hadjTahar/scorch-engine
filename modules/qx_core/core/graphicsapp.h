#ifndef GRAPHICSAPP_H
#define GRAPHICSAPP_H

#include "rootbaseitem.h"
#include "graphicswindow.h"
#include "../timers/timerloop.h"


#include <iostream>
#include <map>

#include <misc/jobsystem.h>

namespace Qx::prv {


class GraphicsApp : public prv::RootBaseItem
{
    QX_META_OBJECT( GraphicsApp, MetaItemType::Root, MetaItemType::Window )

    friend class GraphicsWindow;
public:
    static GraphicsApp *app;

public:
    GraphicsApp(x_real pps, x_real fpsHint );
    virtual ~GraphicsApp();
    void exit( const std::string &reason = "" );


    AppResult init(void **appstate, int argc, char *argv[]);
    AppResult iterate(void *appstate);
    AppResult event(void *appstate, SDL_Event *event);
    void      quit(void *appstate, AppResult result);




private:
    void handleEvent(const SDL_Event * const event);

    void windowAdded( GraphicsWindow *wind );
    void windowRemoved( GraphicsWindow *wind );
    void updateChildren(bool dropFrame);

    void renderToBackend(bool dropFrame );
    GraphicsWindow *window( x_count idx );


private:
    std::map<x_count,
             GraphicsWindow*> m_windows;
    DelayLoop             m_delayLoop;
    bool                  m_exiting;

};


}

#endif // GRAPHICSAPP_H
