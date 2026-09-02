cmake_minimum_required(VERSION 3.16)
set( QX_CMK_MOD_NAME render_backend_filament )
project(${QX_CMK_MOD_NAME} LANGUAGES CXX)



### Add file sources
### ---------------
file(GLOB_RECURSE SAMPLE_SRC_FILES *.h *.cpp)

add_library(${QX_CMK_MOD_NAME} STATIC ${SAMPLE_SRC_FILES} )
target_compile_features(${QX_CMK_MOD_NAME} PUBLIC cxx_std_20)



# Header includes
target_include_directories(${QX_CMK_MOD_NAME} PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
target_link_libraries( ${QX_CMK_MOD_NAME} PUBLIC qx )


# Filament
### ---------------
target_include_directories( ${QX_CMK_MOD_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/vendors/filament/filament/include" )
target_link_libraries( ${QX_CMK_MOD_NAME} PUBLIC filament )

### This function defines how the end-target links it
### Use full links, using "CMAKE_SOURCE_DIR"
### Don't use "PROJECT_NAME"
### ---------------------------------------------------

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_${QX_CMK_MOD_NAME} target )
    target_include_directories( ${target} PUBLIC "${CMAKE_SOURCE_DIR}/modules/render_backend_filament" )
    target_link_libraries( ${target} PUBLIC render_backend_filament )
endfunction()
