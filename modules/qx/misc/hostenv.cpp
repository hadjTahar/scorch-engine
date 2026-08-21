#include "hostenv.h"
#include <thread>


namespace Qx::HostEnv {

x_string App::m_orgName = "";
x_string App::m_appName = "";

unsigned int OS::cpuCoreCount()
{
    const auto cores = std::thread::hardware_concurrency();
    return (cores > 0) ? cores : 2;
}

}
