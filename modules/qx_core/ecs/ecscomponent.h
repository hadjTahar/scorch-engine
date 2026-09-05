#ifndef ECSCOMPONENT_H
#define ECSCOMPONENT_H

#include <components/corecomponent.h>
#include <misc/hostenv.h>
#include <flecs.h>



namespace Qx {

class ECSComponent : public prv::CoreComponent
{
public:

    ECSComponent(prv::GraphicsItem *gItem):
        CoreComponent{ gItem }
    {
        const auto coreCnt = HostEnv::OS::cpuCoreCount();
        m_ecsWorld.set_threads( coreCnt );
        process = [this](x_real dlt)
        {
            if( !m_init && init ){
                m_init = true;
                init();
            }
            if( preProgress )
                preProgress();
            m_ecsWorld.progress( dlt );
            if( postProgress )
                postProgress();
        };
    }
    flecs::world *ecsWorld()
    {
        return &m_ecsWorld;
    }

    prv::x_simpleCallback init;
    prv::x_simpleCallback preProgress;
    prv::x_simpleCallback postProgress;

protected:

    flecs::world m_ecsWorld;
    bool         m_init{false};

};

}
#endif // ECSCOMPONENT_H
