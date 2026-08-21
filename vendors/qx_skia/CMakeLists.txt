cmake_minimum_required(VERSION 3.16)
project(qx_skia LANGUAGES CXX)


add_library(qx_skia STATIC IMPORTED)

### Find skia.lib and link it
### -------------------------
set(QX_SKIA_FILE_NAME "skia")

set( QX_CMK_SKIA_LIB_PATH "${CMAKE_SOURCE_DIR}/vendors/qx_skia/lib")
find_library(SKIA_LIB
    NAMES ${QX_SKIA_FILE_NAME}
    PATHS ${QX_CMK_SKIA_LIB_PATH})

message( "**************************" )
message( ${QX_SKIA_FILE_NAME} )
message( ${SKIA_LIB} )
if(SKIA_LIB)
    message(STATUS "Skia library found at: ${SKIA_LIB}")
else()
    message(FATAL_ERROR "QX-Error: No ${QX_SKIA_LIB_FILE} in: ${QX_CMK_SKIA_LIB_PATH}")
endif()
target_link_libraries(qx PRIVATE ${SKIA_LIB})

### Link libraries needed by skia
### -------------------------

if(NOT DEFINED QX_OPT_CANVAS_BACKEND)
    message(FATAL_ERROR "QX-Error: QX_OPT_CANVAS_BACKEND not set")
endif()
message(STATUS "Skia backend selected: ${QX_OPT_CANVAS_BACKEND}")


if(QX_OPT_CANVAS_BACKEND STREQUAL "sdl_null")
elseif(QX_OPT_CANVAS_BACKEND STREQUAL "sdl_raster")
elseif(QX_OPT_CANVAS_BACKEND STREQUAL "sdl_gpu")
elseif(QX_OPT_CANVAS_BACKEND STREQUAL "skia_raster")
    message(STATUS "Using CPU raster backend")
elseif(QX_OPT_CANVAS_BACKEND STREQUAL "skia_opengl")

    if(WIN32)
        target_link_libraries(qx_skia PRIVATE opengl32)
    elseif(APPLE)
        target_link_libraries(qx_skia PRIVATE "-framework OpenGL")
    elseif(ANDROID)
        target_link_libraries(qx_skia PRIVATE GLESv3 EGL)
    else()
        target_link_libraries(qx_skia PRIVATE GL GLX EGL)
    endif()

elseif(QX_OPT_CANVAS_BACKEND STREQUAL "skia_direct3d")

    if(WIN32)
        target_link_libraries(qx_skia PRIVATE d3d11 dxgi d3dcompiler)
    else()
        message(FATAL_ERROR "QX-Error: Direct3D only supported on Windows")
    endif()

elseif(QX_OPT_CANVAS_BACKEND STREQUAL "skia_vulkan")

    if(WIN32)
        target_link_libraries(qx_skia PRIVATE vulkan-1)
    else()
        target_link_libraries(qx_skia PRIVATE vulkan)
    endif()

elseif(QX_OPT_CANVAS_BACKEND STREQUAL "skia_metal")

    if(APPLE)
        target_link_libraries(qx_skia PRIVATE "-framework Metal" "-framework QuartzCore")
        if(IOS)
            target_link_libraries(qx_skia PRIVATE "-framework CoreGraphics")
        endif()
    else()
        message(FATAL_ERROR "QX-Error: Metal only supported on Apple platforms")
    endif()

elseif(QX_OPT_CANVAS_BACKEND STREQUAL "skia_dawn")

    message(STATUS "Using Dawn (WebGPU) backend")

    if(WIN32)
        target_link_libraries(qx_skia PRIVATE dawn_native dawn_proc dxgi d3d12)
    elseif(APPLE)
        target_link_libraries(qx_skia PRIVATE dawn_native dawn_proc "-framework Metal" "-framework QuartzCore")
        if(IOS)
            target_link_libraries(qx_skia PRIVATE "-framework CoreGraphics")
        endif()
    else()
        target_link_libraries(qx_skia PRIVATE dawn_native dawn_proc vulkan)
    endif()

else()
    message(FATAL_ERROR "QX-Error: Unknown Skia backend: ${QX_OPT_CANVAS_BACKEND}")
endif()
