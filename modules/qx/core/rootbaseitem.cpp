#include "rootbaseitem.h"

namespace Qx::prv
{

RootBaseItem::RootBaseItem():
    CoreItem{ nullptr }
{
    m_itemType = ItemType::Root;
}

RootBaseItem::~RootBaseItem()
{
    Qx::prv::MetaObject::checkRecords( this );
}

}
