/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Line.h"

Line::Line(const gchar *nome, const gchar *tipo, gdouble inicial_x, gdouble inicial_y, gdouble final_x, gdouble final_y) : Drawable(nome,tipo,inicial_x,inicial_y) {
	// TODO Auto-generated constructor stub
	this->final_x = final_x;
	this->final_y = final_y;

}

Line::~Line() {
	// TODO Auto-generated destructor stub
}

void Line::draw(cairo_t* cr){
	//TODO fazer transformação de viewport antes
	cairo_move_to(cr, this->getX(), this->getY());
	cairo_line_to(cr, this->final_x, this->final_y);
}
