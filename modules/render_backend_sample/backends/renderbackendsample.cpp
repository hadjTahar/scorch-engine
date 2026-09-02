#include "renderbackendsample.h"

namespace Qx::Backend
{

RenderBackendSample::RenderBackendSample(prv::GraphicsWindow *winItm):
    prv::RenderBackendBase{ winItm }
{

}

prv::BackendResult RenderBackendSample::initBackend(const x_size &sz)
{
    return prv::BackendResult::SUCCESS;
}

prv::BackendResult RenderBackendSample::beginFrame()
{
    return prv::BackendResult::SUCCESS;
}

prv::BackendResult RenderBackendSample::endFrame()
{
    return prv::BackendResult::SUCCESS;
}

prv::BackendResult RenderBackendSample::renderGraphicsView(prv::GraphicsView *grphxView,
                                                           x_count viewIndex)
{
    return prv::BackendResult::SUCCESS;
}

prv::BackendResult RenderBackendSample::renderMeshModel(GraphicsMeshModel *mshModel)
{
    return prv::BackendResult::SUCCESS;
}

void RenderBackendSample::printTrackers()
{

}

std::unique_ptr<GraphicsMeshModel> RenderBackendSample::createMeshModel()
{
    auto ret = make_unique_meta<GraphicsMeshModel>();
    return std::move( ret );
}

}

