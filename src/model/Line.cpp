/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Line.h"

#include <assert.h>

 Line::Line(const gchar * nome, double inicial_x, double inicial_y, double final_x, double final_y) : Drawable(nome, inicial_x, inicial_y)
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

void Line::draw(cairo_surface_t *surface)
{
	assert(surface);
	_cr = cairo_create(surface);
	cairo_move_to(_cr, _position.x, _position.y);
	cairo_line_to(_cr, _final_position.x, _final_position.y);
	cairo_stroke(_cr);
}
