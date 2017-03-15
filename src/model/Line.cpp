/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Line.h"
#include "model/Viewport.h"

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

void Line::draw(cairo_t *_cr, Viewport *viewport)
{
	//assert(surface);
	//_cr = cairo_create(surface);
	cairo_move_to(_cr, viewport->transformX(_position.x), viewport->transformY(_position.y));
	cairo_line_to(_cr, viewport->transformX(_final_position.x), viewport->transformY(_final_position.y));
	//cairo_destroy(_cr);

}
