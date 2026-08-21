cmake_minimum_required(VERSION 3.16)
project(qx LANGUAGES CXX)


if( QX_OPT_ENABLE_OPENMP )
    find_package(OpenMP REQUIRED)
endif()



# Add file sources Qx
### ---------------
file(GLOB_RECURSE QX_SRC_FILES *.h *.cpp)
list(FILTER QX_SRC_FILES EXCLUDE REGEX ".*/canvas_backends/.*")
list(APPEND QX_SRC_FILES
    "rendering/canvas_backends/${QX_OPT_CANVAS_BACKEND}.h"
    "rendering/canvas_backends/${QX_OPT_CANVAS_BACKEND}.cpp"
)

# SKIA Canvas
### ---------------
if( QX_CMK_CANVAS_SKIA )
    list(APPEND QX_SRC_FILES
        "rendering/canvas_backends/skia_helpers.h"
        "rendering/canvas_backends/skia_base.h"
        "rendering/canvas_backends/skia_base.cpp"
    )
endif()


add_library(qx STATIC ${QX_SRC_FILES} )

target_compile_features(qx PUBLIC cxx_std_20)
target_include_directories( qx PUBLIC "." )
include( "${CMAKE_SOURCE_DIR}/cmakes/defs.cmake" )


# glm
### ---------------
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/glm" )
target_link_libraries( qx PUBLIC "glm::glm" )

# SDL3
### ---------------
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/sdl/include" )
target_link_libraries( qx PUBLIC ${QX_CMK_SDL_LIB_NAME} )

# Yoga
### ---------------
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/Yoga/Yoga" )
target_link_libraries( qx PUBLIC yogacore )

# Filament
### ---------------
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/filament/filament/include" )
target_link_libraries( qx PUBLIC filament )

# Flecs
### ---------------
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/flecs/include" )
target_link_libraries( qx PUBLIC flecs_static )


# qx_skia
### ---------------
### For Qx includes
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/qx_skia" )
### For Skia internal includes
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/qx_skia/skia" )
### INTERFACE only, no need to link
# target_link_libraries( qx PUBLIC qx_skia )



# FreeType
# target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/freetype/include" )
# target_link_libraries( qx PUBLIC freetype )


# Header only
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/headers" )
# target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/headers" )


# OpenMP
if( QX_OPT_ENABLE_OPENMP )
    target_link_libraries( qx PUBLIC OpenMP::OpenMP_CXX)
endif()

