/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Line.h"

Line::Line(const gchar *nome, gdouble inicial_x, gdouble inicial_y, gdouble final_x, gdouble final_y) : Drawable(nome,inicial_x,inicial_y)
{
	// TODO Auto-generated constructor stub

	this->_final_position = Vector(final_x, final_y);

}

 Line::Line(const gchar * nome, double inicial_x, double inicial_y, double final_x, double final_y) : Drawable(nome, inicial_x, inicial_y)
 {
	 this->_final_position = Vector(final_x, final_y);
 }

Line::~Line()
{
	// TODO Auto-generated destructor stub
}

void Line::draw(cairo_t* cr)
{
	//TODO fazer transformação de viewport antes
	cairo_move_to(cr, _position.x, _position.y);
	cairo_line_to(cr, _final_position.x, _final_position.y);
}
