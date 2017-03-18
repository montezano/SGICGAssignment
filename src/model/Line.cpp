/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "Line.h"
#include "Viewport.h"

#include <assert.h>

 Line::Line(const gchar * nome, float inicial_x, float inicial_y, float final_x, float final_y) : Drawable(nome, inicial_x, inicial_y)
 {
	 this->_final_position = Vector(final_x, final_y);
 }

 Line::Line(const gchar * nome, Vector init_position, Vector final_position) : Drawable(nome, init_position)
 {
	 this->_nome = nome;
	 this->_final_position = final_position;
 }

Line::~Line()
{
	// TODO Auto-generated destructor stub
}

void Line::draw(cairo_t *_cr, Viewport *viewport)
{
	//assert(surface);
	//_cr = cairo_create(surface);
	cairo_move_to(_cr, viewport->transformX(_position.x), viewport->transformY(_position.y));
	cairo_line_to(_cr, viewport->transformX(_final_position.x), viewport->transformY(_final_position.y));
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
}
