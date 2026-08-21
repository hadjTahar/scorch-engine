#pragma once
#include "qx_db578462fe.h"
#include "qx_edb5b278e5.h"

#include <map>
#include <string>
#include <misc/defs.h>

namespace Qx::prv {

static const std::map<std::string, const x_dataSpan> CompiledDataMap = {
    { ":/test0.md", x_dataSpan(Qx::prv::qx_db578462fe::AssetsData) },
    { ":/test1.md", x_dataSpan(Qx::prv::qx_edb5b278e5::AssetsData) }
};

x_dataSpan readBinData(const x_string &flName)
{
    const auto cnt = Qx::prv::CompiledDataMap.count(flName);
    dbg_assert( cnt != 0 ) << "The requested asset file does not exist: " + flName;
    dbg_assert( cnt == 1)  << "The requested asset exists more than once: " + flName;

    if (cnt > 0)
        return Qx::prv::CompiledDataMap.at(flName);
    return x_dataSpan();
}

} // namespace Qx::prv
