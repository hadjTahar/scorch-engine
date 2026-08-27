cmake_minimum_required(VERSION 3.16)



add_subdirectory( qx qx_build )
# add_subdirectory( module_sample qx_module_sample )

add_subdirectory( canvas_skia_base              qx_canvas_skia_base )
add_subdirectory( canvas_sdl_renderer           qx_canvas_sdl_renderer )
add_subdirectory( canvas_skia_raster_surface    qx_canvas_skia_raster_surface )
add_subdirectory( canvas_skia_raster_texture    qx_canvas_skia_raster_texture )
