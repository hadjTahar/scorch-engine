cmake_minimum_required(VERSION 3.16)
project(tests LANGUAGES CXX)



## Tests
add_subdirectory( tree_tests )
add_subdirectory( timer_tests )
add_subdirectory( transform_tests )
