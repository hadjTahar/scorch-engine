#include "corecomponent.h"

#include <core/graphicsitem.h>
#include <core/graphicswindow.h>


namespace Qx::prv
{

CoreComponent::CoreComponent(GraphicsItem *gItem):
    m_graphicsItem{ gItem },
    m_windowItem{ nullptr }
{
    m_windowItem = windowItem();
    m_windowItem->addCoreComponent( this );
}

CoreComponent::~CoreComponent()
{
    m_windowItem->remCoreComponent( this );
    // remove();
}

void CoreComponent::remove()
{
    m_graphicsItem->m_removedComponents.push_back( this );
}

GraphicsItem *CoreComponent::graphicsItem() const
{
    return m_graphicsItem;
}

void CoreComponent::processComponent(x_real dlt)
{
    MetaObject::check_is_alive( this );
    if( process )
        process( dlt );
}

GraphicsWindow *CoreComponent::windowItem()
{
    if( m_windowItem )
        return m_windowItem;

    CoreItem *ret = nullptr;
    const auto itm = m_graphicsItem;
    if( itm->isWindowItem() )
        ret = itm;

    else if( itm->m_parent->isWindowItem() )
        ret = itm;
    else
    {
        auto prnt = itm->m_parent;
        /// ## Loop as long as we did not reach root
        ///
        while ( prnt != itm->m_rootItem)
        {
            if( prnt->isWindowItem() )
            {
                ret = prnt;
                break;
            }
            prnt = prnt->m_parent;
        }
    }



    dbg_assert( ret ) << "Could not find window item";
    m_windowItem = CoreItem::castItem<GraphicsWindow,MetaItemType::Window>( ret );
    return m_windowItem;
}



}
