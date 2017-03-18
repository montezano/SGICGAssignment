/*
 * Point.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "Point.h"
#include "Viewport.h"

Point::Point(const gchar *nome, gdouble inicial_x, gdouble inicial_y) : Drawable (nome,inicial_x,inicial_y)
{
	// TODO Auto-generated constructor stub

}
Point::Point(const gchar *nome, Vector init_position) : Drawable (nome, init_position)
{

}

Point::~Point()
{
	// TODO Auto-generated destructor stub
}

void Point::draw(cairo_t *_cr, Viewport *viewport)
{
	//_cr = cairo_create(surface);
	cairo_set_line_width (_cr, 3);
	cairo_set_line_cap  (_cr, CAIRO_LINE_CAP_ROUND); /* Round dot*/
	//TODO fazer transformação viewport antes
	cairo_move_to(_cr, viewport->transformX(_position.x), viewport->transformY(_position.y));
	cairo_line_to(_cr, viewport->transformX(_position.x), viewport->transformY(_position.y));
	//cairo_stroke(_cr);
}

Vector Point::getCenter()
{
	return _position;
}

void Point::transform(Transformation & transformation)
{
	_position = transformation.transformPoint(_position);
}
