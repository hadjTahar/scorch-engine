cmake_minimum_required(VERSION 3.16)
project(scorch_engine LANGUAGES CXX)


## Needed by SKIA
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

### -----------------
### Rendering Options
### ------------------

set( QX_OPT_SDL_INIT_OPTIONS         "SDL_INIT_VIDEO")

### Filament does not like the "SDL_WINDOW_OPENGL" option
set( QX_OPT_SDL_WINDOW_OPTIONS
    "SDL_WINDOW_MAXIMIZED|SDL_WINDOW_RESIZABLE|SDL_WINDOW_HIGH_PIXEL_DENSITY  /*|SDL_WINDOW_OPENGL*/")

### Check "qx/rendering/canvas_backends" for available backends
### Clear the cmake configs, after chaning the backend,
### "skia_opengl" needs "SDL_WINDOW_OPENGL", but filament won't work
set( QX_OPT_CANVAS_BACKEND "skia_raster" )

set(QX_CMK_CANVAS_SKIA "$<$<MATCHES:${QX_OPT_CANVAS_BACKEND},^skia_>:ON,OFF>")


### filament clashes with SDL rendering
### If you want filament 3D along with canvas 2D
### Choose "CanvasTarget::GoolgeFilament"
### For more options check CanvasTarget enum in flags.h
set( QX_OPT_CANVAS_TARGET CanvasTarget::SDLSurface )

set( QX_OPT_ENABLE_2D_Z_SORTING      true )

### -----------------------------------
### Debuggin and optimization Options
### -----------------------------------

set( QX_OPT_MAX_HIERARCHY_LEVEL      9 )



### [0-4]
### 0 : No Print
### 4 : Verbose print
set( QX_OPT_DEBUG_DETAILS            4)


### [0-6]
### For better performance: set it to 0
### 0 : No prints or asserts
### 1 : + dbg_print
### 2 : + dbg_assert
### 3 : + dbg_loop_assert
### 4 : + dbg_error
### 5 : + dbg_warning
### 6 : + dbg_info
### 7 : + dbg_tips
set( QX_OPT_DEBUG_LEVEL              2)



## Disables, asserts, leak tracking, and meta item
set( QX_OPT_ENABLE_META_DEBUGGING    true  )


set( QX_OPT_ENABLE_PRINT_SIZES       false )
set( QX_OPT_ENABLE_FPS_PROBE         true  )
set( QX_OPT_USE_COMPILED_ASSETS      false )
set( QX_OPT_IMMEDIATE_EVENTS         false )
set( QX_OPT_3D_GEOMETRY_TRACKERS     false )



### 12 bytes on 32 is enough for:
# - 1 pointer (usualy this)
# - 2 more 4-bytes floats
set( QX_OPT_TYPED_FUNCTION_CAPTURE_SIZE  12 )
## ON -> TypedFunction. OFF-> std::function.
set( QX_OPT_TYPED_FUNCTION_CALLBACK      false )
set( QX_OPT_DROP_FRAME_DELAY             5  )

set( QX_OPT_VERTEX_COUNT_WARNNING        1000000  )
set( QX_OPT_INDEX_COUNT_WARNNING         3000000  )
set( QX_OPT_ENABLE_OPENMP                false )


## Useful if you have multiple graphics scenes,
## that do not interact with eachother
## like dynamic backgrounds


## These are experimental to see if sorting has an impact
## on performance when adding too many components
## Values can be "SEQ, UNSEQ, PAR, or PAR_UNSEQ"
## https://en.cppreference.com/w/cpp/algorithm/execution_policy_tag.html
## For parallel sorts, I don't know if it causes a data race or note
## So use with caution
set( QX_OPT_PROCESS_COMPONENTS_SORT SEQ )



### -----------------
### Build Options
### ------------------
set( QX_OPT_SDL_STATIC_BUILD         ON )

if( QX_OPT_SDL_STATIC_BUILD )
    set( SDL_STATIC          ON  )
    set( SDL_SHARED          OFF )
    set( BUILD_STATIC_LIBS   ON  )
    set( BUILD_SHARED_LIBS   OFF )
    set( QX_CMK_SDL_LIB_NAME    "SDL3-static")
    set(FLECS_STATIC ON )
else()
    set( SDL_STATIC          OFF )
    set( SDL_SHARED          ON  )
    set( BUILD_STATIC_LIBS   OFF )
    set( BUILD_SHARED_LIBS   ON  )
    set( QX_CMK_SDL_LIB_NAME    "SDL3-shared")
    set(FLECS_SHARED OFF)
endif()



### Modules and vendors
### ----------------
add_subdirectory( modules )
add_subdirectory( vendors )

### Executables
### ----------------

add_subdirectory( examples_2d   examples_2d_build)
# add_subdirectory( examples_3d   examples_3d_build)
# add_subdirectory( tests         tests_build)
# add_subdirectory( benchmarks    benchmarks_build)



### Add "apps", only if it exists
if(EXISTS "apps/CMakeLists.txt")
    add_subdirectory( apps          apps_build)
endif()
