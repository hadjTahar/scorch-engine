#include <core/testitem.h>
#include <gtest/gtest.h>


/*
unit test timer
    Dont use google test

    duration
    loops ( counter )
    callback
    single shot
    drift in 1000, push into a vector

    
    Time the timer
    
- Assert empty Timers

*/



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
