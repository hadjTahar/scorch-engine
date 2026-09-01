
Check the material code
Test without: graphicsMeshModel->ready

- Split the old model between
	- Filement Model : Data buffers
	- Filement Backend : Rendering
- Check that filament backend is destroying everything
- Abstract the filament options, bloom, and render, make them part of GraphicsView
- Viewports:
	- Viewport struct, size, and type
	- Apply the screen size and stretch to the view 
	- m_filamentView->setViewport, size from GraphicsView, fixed or relative
	- Check if you can use a matrix for screen scaling for different dpi add it to camera transforms