# Temporary To do:


qx_3D

add FilamentScene, tips ( choose a filament based canvas for canvas )
	FilamentCanvasScene
 	CanvasScene


If you use Filament with opengl???
If you use Filament Canvas with no filament??

----------------------------------------------------------------------------------------
Use this approach
	- Don't init filament, unless it's requested
	- Both FilamentScene and Filament Canvas, can request filament
	- And it's on them to initialize it, if null, from the window


Remove scen2D, 3D
Add RenderBackend 
		CanvasBase
		3DBase
		with virtual or static renderViews(views, items)
		Then add the Back end to the scene


----------------------------------------------------------------------------------------


skia mods
	canvas_none
	canvas_sdl_raster
	canvas_sdl_gpu

	canvas_skia_raster
	canvas_skia_opengl
	canvas_skia_vulkan



filament based canvas
	FilamentBaseCanvas: base class
	filament_canvas_skia must be raster
	filament_canvas_none
