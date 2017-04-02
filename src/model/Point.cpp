/*
 * Point.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "Point.h"
#include "Viewport.h"

Point::Point(const gchar *nome, gdouble inicial_x, gdouble inicial_y, Windowport *window, Command *clipping) :
	Drawable(nome, inicial_x, inicial_y, window),
	_visible(true)
{
	_clipping = clipping;
	updateWindow();
}
Point::Point(const gchar *nome, Vector init_position, Windowport *window, Command *clipping) :
	Drawable (nome, init_position, window),
	_visible(true)
{
	_clipping = clipping;
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
	return _position;
}

void Point::transform(Transformation & transformation)
{
	_position = transformation.transformPoint(_position);
	updateWindow();
}

void Point::updateWindow()
{
	_position_window = _window->normalize(_position);
	//const Point point = *this;
	_clipping->execute(this);
}

void Point::setVisible(bool state)
{
	_visible = state;
}
