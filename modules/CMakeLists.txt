cmake_minimum_required(VERSION 3.16)


### ------------------------------------------------------------------------------------
function ( qx_link_opengl target)

    if(WIN32)
        target_link_libraries(${target} PRIVATE opengl32)
    elseif(APPLE)
        target_link_libraries(${target} PRIVATE "-framework OpenGL")
    elseif(ANDROID)
        target_link_libraries(${target} PRIVATE GLESv3 EGL)
    else()
        target_link_libraries(${target} PRIVATE GL GLX EGL)
    endif()
endfunction()
### ------------------------------------------------------------------------------------

function ( qx_link_direct3d target)
    if(WIN32)
            target_link_libraries(${target} PRIVATE d3d11 dxgi d3dcompiler)
        else()
            message(FATAL_ERROR "QX-Error: Direct3D only supported on Windows")
        endif()
endfunction()


### ------------------------------------------------------------------------------------

function ( qx_link_vulkan target)
    if(WIN32)
          target_link_libraries(${target} PRIVATE vulkan-1)
      else()
          target_link_libraries(${target} PRIVATE vulkan)
      endif()
endfunction()

### ------------------------------------------------------------------------------------

function ( qx_link_metal target)
    if(APPLE)
        target_link_libraries(${target} PRIVATE "-framework Metal" "-framework QuartzCore")
        if(IOS)
            target_link_libraries(${target} PRIVATE "-framework CoreGraphics")
        endif()
    else()
        message(FATAL_ERROR "QX-Error: Metal only supported on Apple platforms")
    endif()
endfunction()


### ------------------------------------------------------------------------------------


function ( qx_link_dawn target)
    message(STATUS "Using Dawn (WebGPU) backend")
    if(WIN32)
        target_link_libraries(${target} PRIVATE dawn_native dawn_proc dxgi d3d12)
    elseif(APPLE)
        target_link_libraries(${target} PRIVATE dawn_native dawn_proc "-framework Metal" "-framework QuartzCore")
        if(IOS)
            target_link_libraries(${target} PRIVATE "-framework CoreGraphics")
        endif()
    else()
        target_link_libraries(${target} PRIVATE dawn_native dawn_proc vulkan)
    endif()
endfunction()


### ------------------------------------------------------------------------------------


add_subdirectory( qx_core qx_build )
# add_subdirectory( module_sample qx_module_sample )

### Canvas backends
### ------------------
add_subdirectory( canvas_skia_base              qx_canvas_skia_base )
add_subdirectory( canvas_sdl_renderer           qx_canvas_sdl_renderer )
add_subdirectory( canvas_skia_raster_surface    qx_canvas_skia_raster_surface )
add_subdirectory( canvas_skia_raster_texture    qx_canvas_skia_raster_texture )
add_subdirectory( canvas_skia_opengl_surface    qx_canvas_skia_opengl_surface )
add_subdirectory( canvas_skia_opengl_texture    qx_canvas_skia_opengl_texture )


### 3D render backends
### ------------------
add_subdirectory( render_backend_sample         qx_render_backend_sample )
add_subdirectory( render_backend_filament       qx_render_backend_filament )


### Physics
### ------------------
add_subdirectory( physics_box2d                 qx_physics_box2d )








