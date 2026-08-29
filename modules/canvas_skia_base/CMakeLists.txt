cmake_minimum_required(VERSION 3.16)
project(canvas_skia_base LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(canvas_skia_base STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(canvas_skia_base PUBLIC cxx_std_20)



# Header includes
target_include_directories(canvas_skia_base PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
# Link qx
target_link_libraries( canvas_skia_base PUBLIC qx )


### Link SKIA (vendors/qx_skia)
### ---------------
### For Qx includes
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/qx_skia" )
### For Skia internal includes
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/qx_skia/skia" )
### INTERFACE only, no need to link
# target_link_libraries( qx PUBLIC qx_skia )


