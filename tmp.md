# Temporary To do:


qx_3D

add FilamentScene, tips ( choose a filament based canvas for canvas )
	FilamentCanvasScene
 	CanvasScene


If you use Filament with opengl???
If you use Filament Canvas with no filament??

----------------------------------------------------------------------------------------
Use this approach
Don't init filament, unless it's requested
Both FilamentScene and Filament Canvas, can request filament

----------------------------------------------------------------------------------------


FilamentWindow
	filamentBaseCanvas
	if used automaicly use skia_raster


skia mods
	canvas_none

	canvas_sdl_raster
	canvas_sdl_gpu

	canvas_skia_raster
	canvas_skia_opengl
	canvas_skia_vulkan

	



filament based canvas
	FilamentBaseCanvas class
	filament_canvas_skia
		### Raster into filament, instead of sdl renderer
		### assert filament can't be null
		### Check if filament is not null
		### if null, 
		### print( filament must be linked )
	filament_canvas_none
		### Raster into filament, instead of sdl renderer
		### assert filament can't be null
		### Check if filament is not null
		### if null, 
		### print( filament must be linked )