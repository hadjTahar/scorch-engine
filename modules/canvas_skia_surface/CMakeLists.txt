cmake_minimum_required(VERSION 3.16)
project(canvas_skia_surface LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(canvas_skia_surface STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(canvas_skia_surface PUBLIC cxx_std_20)



# Header includes
target_include_directories(canvas_skia_surface PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
# Link qx
target_link_libraries( canvas_skia_surface PUBLIC qx )


# Link Skia
### ---------------
### For Qx includes
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/qx_skia" )
### For Skia internal includes
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/qx_skia/skia" )
### INTERFACE only, no need to link
# target_link_libraries( qx PUBLIC qx_skia )






### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_canvas_skia_surface target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/canvas_skia_surface" )
    target_link_libraries( ${target} PUBLIC canvas_skia_surface )
endfunction()
