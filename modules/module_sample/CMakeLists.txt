cmake_minimum_required(VERSION 3.16)
project(module_sample LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(module_sample STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(module_sample PUBLIC cxx_std_20)

### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"

### ---------------------------------------------------

function( qx_link_module_sample target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/module_sample" )
    target_link_libraries( ${target} PUBLIC module_sample )
endfunction()
