cmake_minimum_required(VERSION 3.16)
project(canvas_sdl_renderer LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(canvas_sdl_renderer STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(canvas_sdl_renderer PUBLIC cxx_std_20)



# Header includes
target_include_directories(canvas_sdl_renderer PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
# Link qx
target_link_libraries( canvas_sdl_renderer PUBLIC qx )


### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_canvas_sdl_renderer target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/canvas_sdl_renderer" )
    target_link_libraries( ${target} PUBLIC canvas_sdl_renderer )
endfunction()
