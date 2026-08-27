cmake_minimum_required(VERSION 3.16)
project(canvas_skia_raster_texture LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(canvas_skia_raster_texture STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(canvas_skia_raster_texture PUBLIC cxx_std_20)



# Link qx
target_include_directories(canvas_skia_raster_texture PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
target_link_libraries( canvas_skia_raster_texture PUBLIC qx )

# # Link qx_skia
# target_include_directories(canvas_skia_raster_texture PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
# target_link_libraries( canvas_skia_raster_texture PUBLIC qx )





### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_canvas_skia_raster_texture target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/canvas_skia_raster_texture" )
    target_link_libraries( ${target} PUBLIC canvas_skia_raster_texture )
endfunction()
