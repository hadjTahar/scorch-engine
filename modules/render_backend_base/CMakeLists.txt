cmake_minimum_required(VERSION 3.16)
project(render_backend_base LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(render_backend_base STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(render_backend_base PUBLIC cxx_std_20)



# Header includes
target_include_directories(render_backend_base PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
# Link qx
target_link_libraries( render_backend_base PUBLIC qx )


### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_render_backend_base target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/render_backend_base" )
    target_link_libraries( ${target} PUBLIC render_backend_base )
endfunction()
