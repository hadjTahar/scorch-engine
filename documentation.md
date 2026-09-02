
### Docs:

**Most of this is deprecated, needs some updates**

The vertices are deinterleaved: vertex GPU representation not [P UV C]

**Interleaved**: Data looks like this in memory:

P N UV | P N UV | P N UV | P N UV ...

**deinterleaved**: Data looks like this in memory:

POSITIONS: P P P P P P ...
NORMALS:   N N N N N N ...
UVS:       UV UV UV UV ...




Filament backend for now only supports beign used for one scene only

### Transforms:

Why different names? because I may be wrong about certain transforms and how each should have been implemented, so I know where each function is called, if I decided to make changes.

    - ItemTransform::physicsTransform
        - Is just the worldTransform
        - Used for physics, not pivot needed
    - ItemTransform::layoutsTransform
        - Is just the worldTransform
        - Used for layouts, to check if we need to re-calculate layouts
    - ItemTransform::pivotTransform
        - Filament already handles camera for us
        - For 3D render
    - ItemTransform::cameraTransform( view , camera)
        - For 2D render, we handle the camera ourselves
        - Mouse events checking

### Level of details 

Level of details 
If .lod is true compute the distance from camera and pass it to render Item and update model


float lodFactor =
glm::clamp(distance / camera.farPlane, 0.0f, 1.0f);

0.0 ───── 0.25 ───── 0.55 ───── 0.8 ───── 1.0
           │          │          │         │
          HIGH      MEDIUM      LOW      CULLED


enum class DetailsLevel : uint8_t {
    None,
    Ignore = None, /// ??
    High,
    Medium,
    Low,
    Culled
};


#### Important concepts and notes:

- Rendering: Uses ::renderingTransform()
- Physics: Uses ::physicsTransform()
- Collisions, mouse events: Uses ::physicsTransform()
- Layout system: Is not concerned with the transform matrix
- Planning to add material design for android and default themes for other platforms, but that's a lots of work and a whole project on its own

renderingTransform and physicsTransform are the same, but different calls, just in case things need to change.



#### Debugging

Heavy use of assertions throughout the code, I believe in "An assertion aday, keeps the bugs away", the compiler may not save you, but future-you will appreciate the warning shot.


#### Naming conventions

Naming conventions are borrowed from Qt

- Class names: CamelCase, starting with an Upper case
- var names: camelCase, starting with an lower case
- trivial types or type aliases:
    - x_name: for general use case
    - v_name: for 3D




#### Qt creator build preference:
- "D:/builds/build/%{Project:Name}/%{Asciify:%{Kit:FileSystemName}-%{BuildConfig:Name}}"




### Build options and macros:

- QX_OPT: Options to control builds used in cmake files
- QX_CMK: cmake internal variables inside cmake files
- QX_DEF: C++ definitions added by cmake
- dbg_  : Debug Macros defined in source code, likely "common/dbg" folder

All options are editable at the cmake level, except QX_OPT_ENABLE_TRACKER, in : "debugtracker.h" (is this still valid???)


## Options
### Print debugging verbose level

QX_OPT_PRINT_LEVEL
  - 0 Disable printing
  - 1 Print message
  - 2 Print dbg prefix ( Debug, error, ...)
  - 3 Print method
  - 4 Print type name
  - 5 Print node name


### Loops:

- Event loop SDL_iterate
Loops:
   1 - windows loop
   2 - layers loop
   3 - Components process loop
   4 - Item updateItem loop
      Loops only if property flag values changed
   5 - Item render loops
         Loops only if property flag values changed
   6 - Views loops
   6 - Components render loops??


The property flag propagates upwards, from child items to parent until window, and can be changed with

If no changes are detected, only loops (1,2 and 3) are run

- Process
- Timers
- Events



### Classes
#### Objects (scene tree)

<pre>
App
 └─ Windows
     └─ Layers
         └─ Views (camera + bounds)
</pre>


- An app can have multiple windows
- Each window can have mutiple graphic layers
- Each graphic layer, can have multiple views( camera, bounds) 

- App
	- Windows
		- GraphicsLayer:
			- GraphicsItems: process, create RenderObjects and adds them to root or graphicslayer
			- ::updateItem, runs in a thread if "QX_OPT_THREADED_UPDATE_ITEMS" is enabled
			- ::Views
					- Camera: Transforms and renders the scene to the view
			- ::Spatial tree (quad, ....)
			- ::Canvas (2D backend)
					- An abstraction for the backend and holds the backend objects and types it gets passed to the, GraphicsItem::render,  it renders the same scene to multiple views
					- Skia, ThorVG, Blend2D
			- ::SceneView (3D backend)



### Rendering API's abstractions
- Canvas Back end API
	- ( skia, SDL, ... )
- Canvas API
	- Abstraction for the Canvas Back end
- Scene graph API
	- QML and Godot like


There are two main classes 

- Items: For rendering
- Components:Behavior: mouse events, animations, timers

#### Rendering (backends)



 
### 2D VS 3D

- GraphicsItem
  - 
	- propagates ::render from "GraphicsItem::propertyChanged"      
  - GraphicsItem2D
    - ::render( Canvas)
    - ::canvas->draw
  - GraphicsItem3D
    - ::GraphicsLayer2D ::graphicsLayer
    - ::render( RenderContext )
    - ::RenderContext->addModel()

- Views
  - Has a viewport transform
  - HAs a camera transform
  - To render you, apply the viewport transform, then the camera transform to the canvas or context
  - Loop and render the items with a lod
  - You can’t remove views once added, only hide them.

### Transform matrix:


Item rendering and draw calls should be done irrelevant to the transformation matrix, position 

Transformation matrix is used for :
- Physics engine 
- Collision detection 
- Final Rendering batch by the canvas and google filament


### Mouse events:
  - Maps the mouse coordinates to the views coords
  - Loop the mouse components and check

#### Dynamic behavior

- Timers
   - Looped Timers
   - Singleshot Timers
- Components:
   - ::process
   - DynamicEase ( Linear, Bezier, Damped and CSS like Polynomial Eases )

### Components

    When a new components is added, the components are sorted by their parentItem hierarchy,
    to ensure CoreComponent::process calls, are called properly.
    If there is a lag or a delay, probably it's a sorting issue
   
### Camel case vs snake case convention

For dev functions and names camel case is used, but snake case for debugging utilities, like dbg_print, dbg_assert

