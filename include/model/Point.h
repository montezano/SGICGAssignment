/*
 * Point.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_POINT_H_
#define SRC_MODEL_POINT_H_

#include "model/Drawable.h"
#include <gtk/gtk.h>

class Point : public Drawable {

public:
	Point(const gchar *nome, gdouble inicial_x, gdouble inicial_y);
	virtual ~Point();
	virtual void draw(cairo_surface_t *surface);
};

#endif /* SRC_MODEL_POINT_H_ */
