#include "Point.h"
#include "Viewport.h"

Point::Point(const gchar *nome, Vector *init_position, Windowport *window) :
	Drawable (nome, init_position, window)
{
	_tipo = "ponto";
	updateWindow();
}

Point::~Point()
{
	// TODO Auto-generated destructor stub
}

void Point::draw(cairo_t *_cr, Viewport *viewport)
{
	if (_visible)
	{
		cairo_set_line_width(_cr, 3);
		cairo_set_line_cap(_cr, CAIRO_LINE_CAP_ROUND); /* Round dot*/
		cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_position_window)), viewport->transformY(_window->unormalize_y(_position_window)));
		cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_position_window)), viewport->transformY(_window->unormalize_y(_position_window)));
	}
}

Vector Point::getCenter()
{
	return *_position;
}

void Point::transform(Transformation & transformation)
{
	*_position_window = transformation.transformPoint(*_position);
	updateWindow();
}

void Point::updateWindow()
{
	_position_window = _window->project(_position);

	clip();
}

void Point::clip()
{
	pointClip();
}

void Point::pointClip()
{
	if (_position_window->x > -1.f && _position_window->y > -1.f && _position_window->x < 1.f && _position_window->y < 1.f)
	{
		_visible = true;
	}
	else
	{
		_visible = false;
	}
}