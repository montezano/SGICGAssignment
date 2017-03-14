#include "model/Canvas.h"

#include <assert.h>

Canvas::Canvas(cairo_surface_t *surface)
{
	assert(_surface);
	_surface = surface;
}

Canvas::~Canvas()
{

}

void Canvas::addDrawable(Drawable* d)
{
	this->notify(static_cast<void*>(d), Events::ADD_DRAWABLE);
	_canvas.push_back(static_cast<Drawable*>(d));
}



void Canvas::drawCanvas()
{
	assert(_surface);
	for(auto drawable: _canvas)
	{
		drawable->draw(_surface);
		g_print(drawable->getNome());
	}
}
