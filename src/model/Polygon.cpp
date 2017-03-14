/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Polygon.h"

#include <assert.h>

 Polygon::Polygon(const gchar * nome, double inicial_x, double inicial_y, std::vector<Vector> coords) : Drawable(nome, inicial_x, inicial_y)
 {
	 this->_coords = coords;
 }

 Polygon::Polygon(const gchar * nome, Vector init_position, std::vector<Vector> coords) : Drawable(nome, init_position)
 {
   this->_nome = nome;
	 this->_coords = coords;
 }

Polygon::~Polygon()
{
	// TODO Auto-generated destructor stub
}

void Polygon::draw(cairo_surface_t *surface)
{

}
