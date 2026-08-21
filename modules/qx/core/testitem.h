#ifndef TEST_ITEM_H
#define TEST_ITEM_H

#include "rootbaseitem.h"




namespace Qx::prv::tests {

class TestRootItem : public RootBaseItem
{
    QX_META_OBJECT( TestRootItem,
                   MetaItemType::Root,
                   MetaItemType::Test )

public:
    TestRootItem():RootBaseItem{}
    {
    }
    ~TestRootItem(){}
    using CoreItem::stepPendings;


};

class TestItem : public CoreItem
{
    QX_META_OBJECT( TestItem,
                   MetaItemType::Test,
                   MetaItemType::Test )
public:
    TestItem(CoreItem *parent):CoreItem{parent}
    {
        m_itemType = ItemType::TestItem;
    }
    ~TestItem(){}
    using CoreItem::stepPendings;

protected:
    void render(Canvas*)override final{}
};



}


#endif // TEST_ITEM_H
