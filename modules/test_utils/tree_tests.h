#ifndef TREE_TESTS_H
#define TREE_TESTS_H

#include <core/testitem.h>


/*
unit test
    remove_test
    ADD_LAYER_TEST
        ADD_LAYER_1_TEST ( root, counter)
        ADD_LAYER_2_TEST ( root, counter, counter )
        ADD_LAYER_3_TEST ( root, counter, counter )

    ADD_REMOVE_LAYER_TEST
        ADD_LAYER_1_TEST ( root, counter)
        ADD_LAYER_2_TEST ( root, counter, counter )
        ADD_LAYER_3_TEST ( root, counter, counter )

    Gpt:: tree test
    Add 100, 1000, 10000
    Remove sequential
    Remove at random

*/



namespace Qx::prv::tests
{

struct TestValue
{
    x_index size{999999};
    x_index counter{999999};
};


inline TestValue root_test( TestValue  )
{
    TestValue ret;
    {
        auto root   = Qx::prv::CoreItem::addRootItem< Qx::prv::tests::TestRootItem>();
        ret.size    = root->childrenView().size();
        ret.counter = Qx::prv::ItemTracker::itemCounter;
    }

    return ret;
}

inline TestValue layer_1_add( TestValue val )
{
    TestValue ret;
    {
        auto root = Qx::prv::CoreItem::addRootItem< Qx::prv::tests::TestRootItem>();
        auto itm = root->addItem<Qx::prv::tests::TestItem>();
        Qx::prv::tests::TestRootItem::stepPendings();

        for (int idx = 0; idx < val.size; ++idx)
            itm->addItem<Qx::prv::tests::TestItem>();
        Qx::prv::tests::TestRootItem::stepPendings();


        Qx::prv::tests::TestRootItem::stepPendings();
        ret.size    = itm->childrenView().size();
        ret.counter = Qx::prv::ItemTracker::itemCounter;
    }
    return ret;
}


inline TestValue layer_1_add_remove( TestValue val )
{
    TestValue ret;
    {
        auto root = Qx::prv::CoreItem::addRootItem< Qx::prv::tests::TestRootItem>();
        auto itm = root->addItem<Qx::prv::tests::TestItem>();
        Qx::prv::tests::TestRootItem::stepPendings();

        for (int idx = 0; idx < val.size; ++idx)
            itm->addItem<Qx::prv::tests::TestItem>();
        Qx::prv::tests::TestRootItem::stepPendings();
        itm->removeItem();

        Qx::prv::tests::TestRootItem::stepPendings();
        ret.size    = itm->childrenView().size();
        ret.counter = Qx::prv::ItemTracker::itemCounter;
    }
    return ret;
}

inline TestValue layer_1_clear( TestValue val )
{
    {
        auto root = Qx::prv::CoreItem::addRootItem< Qx::prv::tests::TestRootItem>();
        auto itm  = root->addItem<Qx::prv::tests::TestItem>();
        Qx::prv::tests::TestRootItem::stepPendings();

        for (int idx = 0; idx < val.size; ++idx)
            itm->addItem<Qx::prv::tests::TestItem>();
        Qx::prv::tests::TestRootItem::stepPendings();
    }
    return {Qx::prv::ItemTracker::itemCounter,0};
}




}

#endif // TREE_TESTS_H
