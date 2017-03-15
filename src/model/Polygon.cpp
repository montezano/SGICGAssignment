/*
 * Line.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Polygon.h"
#include "model/Viewport.h"

#include <assert.h>
#include <stdlib.h>

 Polygon::Polygon(const gchar * nome, double inicial_x, double inicial_y, std::vector<Vector> coords) : Drawable(nome, inicial_x, inicial_y),
	 _coords(coords)
 {
 }

 Polygon::Polygon(const gchar * nome, Vector init_position, std::vector<Vector> coords) : Drawable(nome, init_position),
	 _coords(coords)
 {
 }

Polygon::~Polygon()
{
	// TODO Auto-generated destructor stub
}

void Polygon::draw(cairo_t *_cr)

{
	//assert(surface);
	//_cr = cairo_create(surface);
	cairo_move_to(_cr, Viewport::transformX(_position.x), Viewport::transformY(_position.y));

	for (size_t i = 1; i < _coords.size(); i++)
	{
		cairo_line_to(_cr, Viewport::transformX(_coords[i].x), Viewport::transformY(_coords[i].y));
		//cairo_stroke(_cr);
		cairo_move_to(_cr, Viewport::transformX(_coords[i].x), Viewport::transformY(_coords[i].y));

	}
	cairo_line_to(_cr, Viewport::transformX(_position.x), Viewport::transformY(_position.y));
	//cairo_stroke(_cr);
}
