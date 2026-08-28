#include <core/testitem.h>
#include <gtest/gtest.h>


/*
unit test
test math positions
    transform a node (translate, position,....),
    check the child position, rotation, transform matrix

EG: auto object = root->addObject;
Translate the root and see object->position()


*/



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
