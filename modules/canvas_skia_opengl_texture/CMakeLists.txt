cmake_minimum_required(VERSION 3.16)
project(canvas_skia_opengl_texture LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(canvas_skia_opengl_texture STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(canvas_skia_opengl_texture PUBLIC cxx_std_20)



# Link qx
target_include_directories(canvas_skia_opengl_texture PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
target_link_libraries( canvas_skia_opengl_texture PUBLIC qx )

# # Link canvas_skia_base
target_include_directories(canvas_skia_opengl_texture PUBLIC  "${CMAKE_SOURCE_DIR}/modules/canvas_skia_base")
target_link_libraries( canvas_skia_opengl_texture PUBLIC canvas_skia_base )





### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_canvas_skia_opengl_texture target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/canvas_skia_opengl_texture" )
    target_link_libraries( ${target} PUBLIC canvas_skia_opengl_texture )
endfunction()
