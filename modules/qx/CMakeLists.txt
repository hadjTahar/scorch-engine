cmake_minimum_required(VERSION 3.16)
project(qx LANGUAGES CXX)


if( QX_OPT_ENABLE_OPENMP )
    find_package(OpenMP REQUIRED)
endif()



file(GLOB_RECURSE QX_SRC_FILES *.h *.cpp)

add_library(qx STATIC ${QX_SRC_FILES} )

target_compile_features(qx PUBLIC cxx_std_20)
target_include_directories( qx PUBLIC "." )
include( "${CMAKE_SOURCE_DIR}/cmakes/defs.cmake" )

### Name must be qx_link_+module name
### ---------------------------------------------------

function( qx_link_qx target )
    # Header includes
    # target_include_directories(${target} PUBLIC  "${CMAKE_SOURCE_DIR}/qx/src")
    # Link qx
    target_link_libraries( ${target} PUBLIC qx )
endfunction()

### ---------------------------------------------------


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


# Flecs
### ---------------
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/flecs/include" )
target_link_libraries( qx PUBLIC flecs_static )




# FreeType
# target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/freetype/include" )
# target_link_libraries( qx PUBLIC freetype )


# Header only
target_include_directories( qx PUBLIC "${CMAKE_SOURCE_DIR}/vendors/headers" )


# OpenMP
if( QX_OPT_ENABLE_OPENMP )
    target_link_libraries( qx PUBLIC OpenMP::OpenMP_CXX)
endif()

