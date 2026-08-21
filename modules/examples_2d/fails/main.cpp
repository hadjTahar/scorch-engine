// #include <core/testitem.h>




// class NonQXItem : public Qx::prv::tests::TestItem
// {

//     // QX_ITEM( NonQXItem )

// public:
//     NonQXItem(CoreItem *parent): Qx::prv::tests::TestItem{parent}{}

// };



// int main()
// {

//     {
//         auto tmpRoot = Qx::prv::tests::TestItem::addRootItem<Qx::prv::tests::TestRootItem>();

//         /// ## When tmpItm0, tmpItm1, and tmpItm2  are destroyed,
//         /// ## before the ItemTracker::checkRecords()
//         /// ## the parent (tmpRoot), will not find them
//         ///
//         // Qx::prv::tests::TestItem tmpItm0{ tmpRoot.get() };
//         // auto tmpItm2 = std::make_unique<Qx::prv::tests::TestItem>( tmpRoot.get() );


//         /// ## When tmpItm3 is destroyed, at the end of the program
//         /// ## the ItemTracker::checkRecords() will consider it a leak
//         ///
//         // auto tmpItm3 = new Qx::prv::tests::TestItem{ tmpRoot.get() };


//         /// ## This won't compile because
//         /// ## there is no "QX_ITEM( NonQXItem )"
//         // auto tmpItm4 = tmpRoot->addItem<NonQXItem>();

//         /// ## add/remove pending items
//         /// ## not needed when you use Application
//         ///
//         Qx::prv::tests::TestItem::stepPendings();


//         /// ## The correct way to add items
//         /// ## X but this is failing at the moment
//         auto correctItem = tmpRoot->addItem<Qx::prv::tests::TestItem>();
//         Qx::prv::tests::TestItem::stepPendings();

//     }



//     return 0;
// }
