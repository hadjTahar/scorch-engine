#ifndef APPLICATION_H
#define APPLICATION_H

#include "rootbaseitem.h"
#include "windowitem.h"
#include "../timers/timerloop.h"


#include <iostream>
#include <map>

#include <misc/jobsystem.h>

namespace Qx::prv {


class Application : public prv::RootBaseItem
{
    QX_META_OBJECT( Application, MetaItemType::Root, MetaItemType::Window )

    friend class WindowItem;
public:
    static Application *app;

public:
    Application(x_real pps, x_real fpsHint );
    virtual ~Application();
    void exit( const std::string &reason = "" );


    AppResult init(void **appstate, int argc, char *argv[]);
    AppResult iterate(void *appstate);
    AppResult event(void *appstate, SDL_Event *event);
    void      quit(void *appstate, AppResult result);




private:
    void handleEvent(const SDL_Event * const event);

    void windowAdded( WindowItem *wind );
    void windowRemoved( WindowItem *wind );
    void updateChildren(bool dropFrame);

    void renderToBackend(bool dropFrame );
    WindowItem *window( x_count idx );


private:
    std::map<x_count,
             WindowItem*> m_windows;
    DelayLoop             m_delayLoop;
    bool                  m_exiting;

};


}

#endif // APPLICATION_H
