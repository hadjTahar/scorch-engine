#include "../test_utils/tree_tests.h"
#include <gtest/gtest.h>


/*
unit test
    remove_test

    Add layer 2, 3
    Remove sequential
    Remove at random

*/


TEST(TREE_TESTS, ROOT_TEST)
{
    const auto res = Qx::prv::tests::root_test( {} );

    EXPECT_EQ( res.size,   0);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 1);
}

TEST(TREE_TESTS, LAYER_1_ADD_TEST_1)
{

    const auto res = Qx::prv::tests::layer_1_add( {1,0} );
    EXPECT_EQ( res.size,   1);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 3);
}



TEST(TREE_TESTS, LAYER_1_ADD_TEST_10)
{

    const auto res = Qx::prv::tests::layer_1_add( {10,0} );
    EXPECT_EQ( res.size,   10);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 12);
}


TEST(TREE_TESTS, LAYER_1_ADD_TEST_100)
{

    const auto res = Qx::prv::tests::layer_1_add( {100,0} );
    EXPECT_EQ( res.size,   100);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 102);
}


TEST(TREE_TESTS, LAYER_1_ADD_TEST_1000)
{

    const auto res = Qx::prv::tests::layer_1_add( {1000,0} );
    EXPECT_EQ( res.size,   1000);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 1002);
}



TEST(TREE_TESTS, LAYER_1_ADD_TEST_10000)
{
    const auto res = Qx::prv::tests::layer_1_add( {10000,0} );
    EXPECT_EQ( res.size,   10000);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 10002);
}

/// ## ---------------------------------------------------------------
///

TEST(TREE_TESTS, LAYER_1_ADD_REMOVE_TEST_1)
{
    const auto res = Qx::prv::tests::layer_1_add_remove( {1,0} );
    EXPECT_EQ( res.size,   0);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 1);
}



TEST(TREE_TESTS, LAYER_1_ADD_REMOVE_TEST_100)
{
    const auto res = Qx::prv::tests::layer_1_add_remove( {100,0} );
    EXPECT_EQ( res.size,   0);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 1);
}


TEST(TREE_TESTS, LAYER_1_ADD_REMOVE_TEST_10000)
{
    const auto res = Qx::prv::tests::layer_1_add_remove( {10000,0} );
    EXPECT_EQ( res.size,   0);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 1);
}




/// ## ---------------------------------------------------------------
///
TEST(TREE_TESTS, LAYER_1_CLEAR_1)
{
    const auto res = Qx::prv::tests::layer_1_clear( {1,0} );
    EXPECT_EQ( res.size,   0);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 0);
}



TEST(TREE_TESTS, LAYER_1_CLEAR_100000)
{
    const auto res = Qx::prv::tests::layer_1_clear( {10000,0} );
    EXPECT_EQ( res.size, 0);
    if constexpr( !QX_DEF_ENABLE_TRACKER )
        return;
    EXPECT_EQ( res.counter, 0);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
