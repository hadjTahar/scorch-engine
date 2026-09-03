cmake_minimum_required(VERSION 3.16)
project( vendors )




# SDL options
### ---------------
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_DISABLE_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)


## FILAMENT Options
## ---------------


set( FILAMENT_USE_EXTERNAL_GTEST        ON)
set( FILAMENT_SKIP_SDL2                 ON )
set( FILAMENT_SKIP_SAMPLES              ON )
set( FILAMENT_BUILD_FILAMAT             ON )
set( FILAMENT_SUPPORTS_OPENGL           ON )
set( FILAMENT_ENABLE_LTO                OFF )
set( FILAMENT_SUPPORTS_METAL            OFF )
set( FILAMENT_SUPPORTS_VULKAN           OFF )
set( FILAMENT_INSTALL_BACKEND_TEST      OFF )
set( FILAMENT_USE_EXTERNAL_GLES3        OFF )
set( FILAMENT_BUILD_TESTING             OFF )
# set( FILAMENT_ENABLE_MULTIVIEW          OFF )
# set( FILAMENT_ENABLE_EXCEPTIONS         ON  )
# set( FILAMENT_ENABLE_RTTI               OFF )

## google-benchmark Options
set( BENCHMARK_ENABLE_GTEST_TESTS OFF )


add_subdirectory( qx_skia     qx_skia)
add_subdirectory( glm         glm_build)
add_subdirectory( sdl         sdl_build)
add_subdirectory( yoga        yoga_build)
add_subdirectory( filament    filament_build  )
add_subdirectory( flecs       flecs_build  )
add_subdirectory( box2d       box2d_build  )
add_subdirectory( box2dcpp    box2dcpp_build  )
# add_subdirectory( freetype    freetype_build)
add_subdirectory( googletest  googletest_filament_build )
# add_subdirectory( googlebenchmark   googlebenchmark_build)

