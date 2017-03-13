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

void Canvas::addLine(const char *nome, Vector v_inicial, Vector v_final)
{
	_canvas.push_back(static_cast<Drawable*>(new Line(nome, v_inicial, v_final)));
}

void Canvas::drawCanvas()
{
	g_print("era prater desenhado!!\n");
	assert(_surface);
	for(auto drawable: _canvas)
	{
		g_print("no for\n");
		drawable->draw(_surface);
	}
}
