# To do:

- Test and document git config submodule.ignore all

------------------------------------------------------------------------------------

Create type aliases for defs
Add createType( TypeDef )
CreateWorld( World)


------------------------------------------------------------------------------------

- Modules
	  - Ecs
	  - Collision 
	  - layout
	  - Boxes 
	  - State machine
	  - Petri net


- Retest examples

------------------------------------------------------------------------------------

- Level of details 
- If .lod is true compute the distance from camera and pass it to render Item and update model
- float lodFactor =
- glm::clamp(distance / camera.farPlane, 0.0f, 1.0f);
0.0 ───── 0.25 ───── 0.55 ───── 0.8 ───── 1.0
           │          │          │         │
          HIGH      MEDIUM      LOW      CULLED


- enum class DetailsLevel : uint8_t {
	None,
	Ignore = None, /// ??
    High,
    Medium,
    Low,
    Culled
};


------------------------------------------------------------------------------------
- Viewports:
	- Viewport struct, size, and type
	- Apply the screen size and stretch to the view 
	- m_filamentView->setViewport, size from GraphicsView, fixed or relative
	- Check if you can use a matrix for screen scaling for different dpi add it to camera transforms
	- Add reference {Fixed, Relative, Reference} eg: 1920x1080 and scale it to other screens like an image
	- Add screen or view scale transform for eg use base dpi then use the desired dpi as a scale matrix
	- Use the matrix in view
	- Or use sim screen or sim view to simulate different screens
	- Before each window render set current screen and update the viewports and the screen matrix 
	- Window screenTest( size, dpi )
	- Calculate the scale use it in the view
	- dp, px ,…:
		Set a static current screen object and use it for calculations 
		And a static test screen?

------------------------------------------------------------------------------------
- initCanvas to initBackend
- 2d render to draw(Canvas)
- comn_examples, that have nor rendering, like timers nad ecs
- Fix 3D examples
	- Use Flecs as a module
	- Use nanoflann as a module
- Enable disable scene, no render no components process 
- Add colorsPool
	- Update worldItem using colors
	- enableShader/enableMaterial
- Make sure you are not rendering not visable items and off screen, using rendering
	- Create bool offScreen();
	- Create CoreComponent::active| or enabled/disabled, if (!enabled) return, don't call process
		- This allows some items and components to idle
- Fix: Camera controler is flipping the world when mouse clicked
	- Camera click only messes when apply model transform  "tcm.setTransform(instance,filamentMatrix);"
- Trigs vs strips for better performance
- Add TypedFunctions to unit tests
- Filament Canvas:
	- Filament Canvas 
	    - Render to sdl texture then to filament
	    - Take skia snap shot and render it to filament
	    OR
	    - Render to sdl texture then to filament texture
	- CanvasModel cnvsItm = scene.addItem<CanvasModel>
	    - pass it to the scen2D
	    - and use it to render the canvas
	- Remove filament from canvas, and pass either
	    - The window
	    - The model
	    - The Canvas Model
	- GraphicsModelItem
    - GraphicsCanvasItem
- Unit test orphaned items upon destruction 
- Github:
	- Currently tested on windows
	- Contact?
- Remove MetaItemType::Physics
	- Don't use "propagation" and "propagate", just get root or windowItem and set it to needsRendering	
- QX_OPT_SDL_WINDOW_OPTIONS per OS, ask gpt
- Recheck if there are leaks when resizing
- Recheck and Fix the time loop
- Improve or fix the scene graph.
	- look up scene graph data structure and a better traverse 
	- Remove the recursive calls in the scene graph (update, render, ...)
- Refactor modules
	- See if you can use filament and canvas as modules
	- Let skia modules handle all the options 
	- Qx_use_module(skia)
	- Qx_use_module(filament)
	- Enable or disable linking
	- So you can clean up, or commenting out non needed modules on release
	- Nanolann, ECS (ECSComponent), hash maps, filament, skia, and most vendors as modules
	- Doc: modular functionalities, it's up to the end user to use or remove modules
		scene 2D and scene3D as modules???
- Multiple views:
	- Untested
	- Fix or remove multiple views
	- Rename renderItem to renderables()
- Dynamic properry for camera
	- LinearCamera
	- BezierCamera
	- PolynomialCamera
	- DampedCamera
- Mouse event:
	- Replace x y with vector point ::windowPoint 
	- itemPoint (mapped point)
- Mechanics:
	Develop a mechanic class, that handles, that can be fed to an ECS
	- Input: keys or mouse 
	- Detection: collision 
	- Transformation : Move,render, update, animation or rotation
	- Communication : 
		- Or Interaction, update or inform other items or entities. Eg: if a door button is pressed, inform the door to open with a signal, rewards, bullet or hit damage, sound
		- Check Signal from Godot
	- State:  Update internal (relative to the item) logics, memory and states. Eg: opened,closed, hit.

- Editor:
	- Generate item files that later can be used to load the items
	- Add scene 3d
	- Editor use C++ DSPatch for visual programming 
	- Add add canvas scene
	- When you compile and run, add items from the files
	- Check Esoterica engine 
	- You add an item
		- Attach a component, and each component has a panel, options, code, …
	- You can add ECSItem
		- Then add entities
		- And set or add ECSComponent s to each entity 
	- Eg:
		- Add ecs component mesh
		- Add ecs component collision 
		- Add ecs system, then you code the system or use a pre existing one, like gravity, boids system , turret system, 



- Document the classes:
	- Properties, like size, color, and propagation system
	- Items
	- Components
	- Timers
	- Dynamic Properties
	- 2D Canvas
	- 3D Rendering
	- Transforms
	- Views
	- Scenes
	- namespaces
		- Qx
		- prv: is something that the end user probably should not use
	- Modules
		- qx: core module
		- examples
		- tests: unit testing module
		- benchmarks: benchmarks module

- Screen units and screen resolutions
- Remove check property : QX_OPT_CHECK_UPDATE_CHILDREN
- Check skia effects, check:
	- styles.h/CanvasEffects
	- https://skia.org/docs/user/sksl/
	- https://shopify.github.io/react-native-skia/docs/shaders/gradients/
	- https://skia.org/docs/user/api/skpaint_overview/
	- goolge skia gradients
- Add atlas item for emitters and swarms
	- or use ecs for the emitters
- Leaks:
	- Use empty canvas and see where the leaks are
	
- Keyboard events, when exiting cause crash
- Frame transforms interpolation between updates:
  - is this necessary
  - cache the world transform, update
  - virtual ::interpolate??
  - QX_OPT_INTERPOLATE
- Camera Limits
- Strip vs triangles for fast rendering??
- How to add normals??
- Audio with sdl Mixer example 
- Add Page Item for both 2D and 3D, types: stack, swipe, OverLay for games UI
- Clean unnecessary filament includes
- Add options to "scripts/compile_mats.py" with optimized options
- Search for "BackendResult" returns and handle them properly
	- Create Error class, with enum and description
	- And an assert, with the description
	- All errors must be checked, ::check, if not called, assert an uncaught error
	- See if you can replace all the direct assert calls with Error class,
		Eg: Error::assert(), Error::error(), Error::warning()
- Remove "MetaItemType" and use "ItemType" directly for asserting
- More examples
	2D example pivots
	SpriteAnim example
		Load sheet
		Auto index = Add row (x y )
		play index 
		Time speed, fps?
		Or addFrame(index, x, y)
		Play(index)
	- 3D filling a tank with balls test example
	- Inputs example, fix the events
		- It does not allow for multiple keys
		- Using strings interrupts the precvious key
	- Procedural animation example, Velvet integration
	- Behavior tree example, BehaviorTree.CPP
	- Procedural crawlers animation example
	- Box3D wall brick smash
	- A lit cube material, with a light source
	- Load model from file
	- Item controller, with mouse like the camera example 
	- Cube placer, click to place cube on a plane for rts game
	- Bullets example
	- Ballistic example
	- Pendulum 
	- Orbitor
	- https://haxeflixel.com/demos/FlxSpine/
	- CSS Examples : 
    - https://css-tricks.com/how-css-perspective-works/
    - https://animista.net/play/basic/slide-rotate
- Example:
    - https://www.youtube.com/watch?v=27xtugVHhaM
    - https://www.youtube.com/watch?v=N5MveKXGZo0
    - https://www.youtube.com/watch?v=gFObo1K-fk0
    - https://www.youtube.com/watch?v=8v5SrgkC_dI
	- Particle sim with DynamicVelocity and dynamic fade?
	- Add Japan example white and red circle
	- Flight instruments module, Flight Indicator instruments module widgets
    - Pivots: cubes with differnt pivots, check rotatin_cube example
    - Motions: TransformMotion Component, check rotatin_cube example
        rotatorEffect /Component
        BouncerEffect /Component
        SliderEffect /Component
        ShakerEffect /Component
        PulserEffect /Component
        ScalerEffect /Component
- Check if you can use abseil, AnyInvocable for callbacks, like time, container, maps for assets


### On the look-out for

- https://renderdoc.org/
- https://github.com/wolfpld/tracy
- https://github.com/google/sanitizers/wiki/addresssanitizer
- https://github.com/sammycage/lunasvg?tab=readme-ov-file
- https://github.com/litehtml/litehtml
- https://github.com/plutoprint/plutobook
- https://github.com/lumia431/reaction
