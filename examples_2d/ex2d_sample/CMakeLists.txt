cmake_minimum_required(VERSION 3.16)

### ----------------
### App Options
### ----------------


set( QX_CMK_APP_NAME ex2d_sample )
set( QX_CMK_ORG_NAME "QxOrg" )

include( "${CMAKE_SOURCE_DIR}/cmakes/app.cmake" )


qx_use_module( canvas_sdl_renderer )

qx_use_module( canvas_skia_raster_surface )
qx_use_module( canvas_skia_raster_texture )

qx_use_module( canvas_skia_opengl_surface )
qx_use_module( canvas_skia_opengl_texture )
