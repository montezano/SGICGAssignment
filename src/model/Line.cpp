#include "Line.h"
#include "Viewport.h"

#include <assert.h>

 Line::Line(const gchar * nome, float inicial_x, float inicial_y, float final_x, float final_y, Windowport *window) :
	 Drawable(nome, inicial_x, inicial_y, window),
	 _final_position(Vector(final_x, final_y)),
	 _final_position_window(Vector(final_x, final_y))
 {
	 updateWindow();
 }

 Line::Line(const gchar * nome, Vector init_position, Vector final_position, Windowport *window) :
	 Drawable(nome, init_position, window),
	 _final_position(final_position),
	 _final_position_window(final_position)
 {
	 updateWindow();
 }

Line::~Line()
{
	// TODO Auto-generated destructor stub
}

void Line::draw(cairo_t *_cr, Viewport *viewport)
{
	//assert(surface);
	//_cr = cairo_create(surface);
	cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_position_window)), viewport->transformY(_window->unormalize_y(_position_window)));
	cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_final_position_window)), viewport->transformY(_window->unormalize_y(_final_position_window)));
	//cairo_destroy(_cr);

}

Vector Line::getCenter()
{
	return (_position + _final_position) / 2.f;
}

void Line::transform(Transformation & transformation)
{
	_position = transformation.transformPoint(_position);
	_final_position = transformation.transformPoint(_final_position);
	updateWindow();
}

void Line::updateWindow()
{
	_position_window = _window->normalize(_position);
	_final_position_window = _window->normalize(_final_position);
}
