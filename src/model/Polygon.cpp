#include "Polygon.h"
#include "Viewport.h"

#include <assert.h>
#include <stdlib.h>

 Polygon::Polygon(const gchar * nome, double inicial_x, double inicial_y, std::vector<Vector> coords, Windowport *window) :
	 Drawable(nome, inicial_x, inicial_y, window),
	 _coords(coords)
 {
	 updateWindow();
 }

 Polygon::Polygon(const gchar * nome, Vector init_position, std::vector<Vector> coords, Windowport *window) :
	 Drawable(nome, init_position, window),
	 _coords(coords)
 {
	 updateWindow();
 }

Polygon::~Polygon()
{
	// TODO Auto-generated destructor stub
}

void Polygon::draw(cairo_t *_cr, Viewport *viewport)

{
	//assert(surface);
	//_cr = cairo_create(surface);
	cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_position_window)), viewport->transformY(_window->unormalize_y(_position_window)));

	for (size_t i = 1; i < _coords_window.size(); i++)
	{
		cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_coords_window[i])), viewport->transformY(_window->unormalize_y(_coords_window[i])));
		//cairo_stroke(_cr);
		cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_coords_window[i])), viewport->transformY(_window->unormalize_y(_coords_window[i])));

	}
	cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_position_window)), viewport->transformY(_window->unormalize_y(_position_window)));
	//cairo_stroke(_cr);
}

Vector Polygon::getCenter()
{
	Vector sum = _position;
	for (auto vector : _coords)
	{
		sum += vector;
	}

	return sum / static_cast<float>(_coords.size()+1);
}

void Polygon::transform(Transformation & transformation)
{
	_position = transformation.transformPoint(_position);
	for (size_t i = 1; i < _coords.size(); i++)
	{
		_coords[i] = transformation.transformPoint(_coords[i]);
	}

	updateWindow();
}

void Polygon::updateWindow()
{
	_position_window = _window->normalize(_position);
	
	for (size_t i = 1; i < _coords_window.size(); i++)
	{
		_coords_window[i] = _window->normalize(_coords[i]);
	}
}

void Polygon::clip()
{
}
