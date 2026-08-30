#include "graphicsscene3d.h"


#include <utils/EntityManager.h>
#include <filament/Viewport.h>
#include <filament/View.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>

#include <filament/IndexBuffer.h>
#include <filament/VertexBuffer.h>
#include <filament/RenderableManager.h>

#include <filament/Material.h>
#include <filament/MaterialInstance.h>
#include <filament/Camera.h>
#include <filament/Skybox.h>
#include <filament/Engine.h>

------------------------------------------------------------

MeshModelBase

Part data buffers 
Other part backend buffers

But how to set the other half?

------------------------------------------------------------

virtual MeshModelBase RenderBackend::createMeshModel()

If null don’t call updateModel
Rename it to updateMeshModel

FilamantModel : public MeshModelBase

------------------------------------------------------------

Make it private and pass it to updateModel
What about requesting 

------------------------------------------------------------------

FilamentBackend::destroyEngine
m_filamentView->setViewport, size from GraphicsView, fixed or relative
Doc: Filament for now only supports beign used for:
	- One scene only
	- One view only, 
------------------------------------------------------------------

Add multiple views:
	- renderView( view, index )
	- assert the index


