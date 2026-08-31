
- Create "render_backend_sample"
- Split the old model between
	- Filement Model : Data buffers
	- Filement Backend : Rendering
- Check that filament backend is destroying everything
- Abstract the filament options, bloom, and render, make them part of GraphicsView
- m_filamentView->setViewport, size from GraphicsView, fixed or relative
