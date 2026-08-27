Remove filament from window
Except pointers , perhaps make the window own the scene?

Remove filament from model
Add render to the back end

Collect the models then render them like the canvas?

But how to reuse filament vertex and index buffers?

----------------------------------------------------------------------------------------


Keep scene 2d and 3d but instead , each back end
Should define a static renderViews(views, items)



----------------------------------------------------------------------------------------

In rendering back end 

Use std map (model, filament model)

Loop models
Fill the map with the model pointer as key and render 
The problem, is how to know the model was destroyed 

Use a render counter?
Use a clean up loop?

In the 3d item destructor somehow tell the back end to remove the key from the map?
The 3d item needs to hold a pointer to the render back end




----------------------------------------------------------------------------------------


Keep the back end private and null 
Only remove model if backend is not null
Filament model contains a pointer to the model to render in std vector loop
But how the model knows which vector index to remove?
We need an index in the model somehow to know which index to remove when item gets destructed



auto it = std::find(v.begin(), v.end(), value);

if (it != v.end()) {
	/// ## Move element to end, and remove it
	/// ## To avoid moving later elements
    *it = std::move(v.back());
    v.pop_back();
}