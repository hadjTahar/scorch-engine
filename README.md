# scorch-engine

Not useable yet, work in progress...

## What is scorch-engine 

A cross platform game engine/framework, that can be used to develop both 2D and 3D apps using.

It’s a game engine and an application development framework, using open source C++ libraries:
This is a low level game engine, it gives basic features and let’s you build your game style however you wish it to be.


### Vendors:

- SDL3: For windowing
- SKIA: 2D canvas
- Google-filament: For 3D rendering
- Flecs: For ECS
- Yoga-Flex: Layouts

For a complete list check the "vendors" folder.



### Features (as modules ):

- 2D Canvas: 2d vector Canvas rendering from skia
- 3D Rendering: 3d physically based rendering from google filament
- Layouts: from yoga flex
- Ecs: from flecs
- Physics2d from box2d
- Physics3d: box3d
- Material design: work in progress 
- Supports both scene graph and data driven approaches


This is more than adding an abstraction layer on top of other libraries, additional features I added

- Core Loop
- Scene graph
- Process components
- Dynamic properties: bezier, polynomial, and damped
- Flex layouts
- Input events: keys and mouse events
- Compiled assets loading 
- Merging 2d and 3d, with same API

Experimental multiple rendering backends:

- 2D multiple rendering backends
	- SKIA ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square)
	- SDL renderer ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square)
	- ThorVG ❌
	- Blend2D ❌
- 3D multiple rendering backends
	- Google filament ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square)
	- bgfx ❌
	- magnum ❌
- Bridging 3d and 2d ![WIP](https://img.shields.io/badge/WIP-red?style=flat-square)


----------------------------------------------------------------------------------------


## Getting started:

Check [How to build](https://github.com/hadjTahar/scorch-engine#how-to-build)

----------------------------------------------------------------------------------------

## Demos:

Here are some primitive demos

- Rotating cube
- Rotating cubes
- Swarm
- property, rectangle
- Flex Layouts
----------------------------------------------------------------------------------------


## Examples
Check folders "examples_2d" and "examples_3d"

----------------------------------------------------------------------------------------



## Why support this project 

- If you care about C++ being and staying relevant in app and game dev
- Light weight 
- Modular, you only pay for what you use using modules
- Bloat proof, no matter how many features will be added, end user can just unlink un-desired modules in release 


### How to support this project 

- Report issues and bugs
- Try to create simple apps
- Create examples
- Suggest features and how they could be implemented
- Suggest optimizations 

I need help with

- Creating unit tests
- Creating benchmarks
- Finding and reporting bugs
- Creating more examples
- Documentation
- Create helper python scripts for cross platform compilation
- Make sure things compile on other platforms, I only got to work on Windows 10 so far.
- Push the engine to its limits


Now it only supports basic rendering functionalities, but the base is there to make something more powerful, with dedicated work we can take it as far as creating:

- Mobile apps with material design 3
- Desktop apps
- 2D and 3D games for all platforms even consoles.

----------------------------------------------------------------------------------------

## Why I Created scorch-engine


I created **scorch-engine** because none of the existing tools fully matched how I like to work or what I want to build.

I come from a **Qt Scene Graph** background, and I genuinely like its architectural ideas. Many concepts in scorch-engine are inspired by Qt’s approach to scenes, nodes, and rendering. 

However, over time Qt has grown into a very large framework. It’s powerful, but for many projects, especially lightweight apps and games, it can feel **bloated**, with a lot of functionality you don’t always need, and lacks game dev.

**Unreal Engine** is extremely capable, but it is primarily focused on high-end game development. It’s heavy by design, not well suited for general app development, and while mobile support exists, it comes with performance, size, and workflow trade-offs that make it less appealing for small or hybrid app/game projects.

**Godot** is a solid engine, but its workflow is highly editor-driven. For developers who prefer writing systems and code directly, the amount of clicking through menus, inspectors, and editor panels can slow things down and break flow.

**Unity** is powerful and flexible, but it comes with its own complexity, ecosystem lock-in, and design decisions that don’t necessarily align with how I want to structure an engine or framework.

That’s why I created **scorch-engine**.

**Qx is designed to be**:

* **Lightweight by default**
* Capable of handling **both 2D and 3D**
* Suitable for **apps and games**, not just games
* **Code-centric**, with minimal friction
* Modular, so you only use what you actually need


**Scorch-engine exists for developers who**:

* Want to understand their engine, not fight it
* Prefer writing systems over clicking through panels
* Care about performance, binary size, and determinism
* Need one tool for apps, tools, and games

**scorch-engine is trying to solve**:
- Bloat in game engines and frameworks
- One framework to rule them all 2D, 3D, apps and games
- Modular design

**Qx is not, and not trying to be**:
- Large games engine
- Large world game engine
- Certainly not AAA game engine
- Certainly NOT ready yet, even for what it claims

Scorch-engine takes inspiration from scene-graph–based systems like Qt and Godot, where structure, hierarchy, and determinism matter. But unlike large, all-encompassing frameworks, scorch-engine is intentionally lightweight. It avoids bundling features by default and instead focuses on being a clean foundation.

Scorch-engine is not trying to compete head-on with massive engines. Instead, it’s built to give developers a clean, efficient foundation, combining the structural elegance of scene graphs with modern rendering and physics, without the overhead and constraints of larger platforms.

Scorch-engine exists because modern development tools have drifted away from simplicity. Over time, engines and frameworks have grown into massive ecosystems. They are powerful, but heavy. Feature-rich, but rigid. Optimized for every use case, except the one where a developer wants clarity, control, and speed.

Scorch-engine was created as a response to that. It is built on the belief that **an engine should serve the developer, not dictate the workflow**.





----------------------------------------------------------------------------------------


### How to build
---


Build on tested on MSVC-x64


#### Clone and init the repository

- git clone https://github.com/hadjTahar/scorch-engine.git
- cd scorch-engine
- git submodule update --init --recursive


#### Comment out Yoga unit tests

- Open "yoga/CMakeLists.txt"
- Comment out "add_subdirectory(tests)"

#### Build skia

The hardest part is compiling skia, once you build it (skia, good luck with that), rest should be easy

- Windows: 
	- Don't use "CMD" or "Power-shell"
	- Use either "x86 native tools for VS" or "x64 native tools for VS"
- Linux: not tested yet
- run "python init_skia.py"
- Copy "scripts/skia_compiler.py" and option_files.args file
	- Choose based on compiler and backend
- cd vendors/skia
	- This is very important
	- Don't run the python script from "scripts/skia_compiler.py"
	- Copy it and run it from "vendors/skia/"
- Run skia_compiler.py option_files.args file



**Build mismatch**

Sometimes gn defaults to x86, if there is a build mismatch, open toolchain.ninja, and check if command(s) are pointing to the right arch x86/x64 folder.
- x86 : "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/bin"
- x64 : "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin"

For now I change the paths manually, search and replace "x64" with "x86" and it works on windows


##### Bazel

You can build skia, not following these steps, like using "bazel build", just make sure the end lib file is at: "vendors/skia/qx_lib/skia.lib"

Bazel is the recommended way to build skia, but I was not sucessfull so far.


#### Include files

If the build is successful, copy these folders to "vendors/skia/includes":

- include 
- skia (copy include and rename it as skia)
- modules





#### Re-build filament materials

- Cmake "scroch-engine"
- Build scroch-engine, don't run, it will crash
- run compile_mats.py


#### Build scorch-engine

- 