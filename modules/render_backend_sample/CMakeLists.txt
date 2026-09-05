cmake_minimum_required(VERSION 3.16)
set( QX_CMK_MOD_NAME render_backend_sample )
project(${QX_CMK_MOD_NAME} LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(${QX_CMK_MOD_NAME} STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(${QX_CMK_MOD_NAME} PUBLIC cxx_std_20)


# Link qx_core
target_include_directories(${QX_CMK_MOD_NAME} PUBLIC  "${CMAKE_SOURCE_DIR}/qx_core")
target_link_libraries( ${QX_CMK_MOD_NAME} PUBLIC qx_core )

### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_${QX_CMK_MOD_NAME} target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/render_backend_sample" )
    target_link_libraries( ${target} PUBLIC render_backend_sample )
endfunction()
