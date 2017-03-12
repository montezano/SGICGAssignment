/*
 * Point.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Point.h"

Point::Point(const gchar *nome, const gchar *tipo, gdouble inicial_x, gdouble inicial_y) : Drawable (nome,tipo,inicial_x,inicial_y)  {
	// TODO Auto-generated constructor stub

}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

void Point::draw(cairo_t* cr){
	cairo_set_line_width (cr, 50);
	cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND); /* Round dot*/
	//TODO fazer transformação viewport antes
	cairo_move_to(cr, this->getX(), this->getY());
    cairo_line_to(cr, this->getX(), this->getY());

}
