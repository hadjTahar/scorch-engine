#include "graphicsscene.h"

Qx::prv::GraphicsScene::GraphicsScene(CoreItem *parent):
    GraphicsItem{ parent }
{
    m_graphicsScene = this;
}

Qx::prv::GraphicsScene::~GraphicsScene()
{
    m_items.clear();
}

void Qx::prv::GraphicsScene::registerItem(GraphicsItem *itm)
{
    m_items.push_back( itm );
}

void Qx::prv::GraphicsScene::unregisterItem(GraphicsItem *itm)
{
    if( m_items.empty() )
        return;
    auto it = std::find_if(m_items.begin(),
                           m_items.end(),
                           [itm](GraphicsItem *lstItm)
                           {
                               return lstItm == itm;
                           });
    const auto found = (it != m_items.end());
    dbg_assert_st( found ) << "Couldn't find itm in m_items";
    m_items.erase( it );
}



std::vector<Qx::prv::GraphicsItem *> Qx::prv::GraphicsScene::items() const
{
    return m_items;
}

Qx::prv::GraphicsView *Qx::prv::GraphicsScene::addView()
{
    auto ptr = std::make_unique<GraphicsView>( this, x_rect{}, ViewType::Absolute );
    auto ret = ptr.get();
    m_views.push_back( std::move( ptr ) );

    return ret;
}


