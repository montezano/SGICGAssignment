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
	Point(const gchar *nome, const gchar *tipo, gdouble inicial_x, gdouble inicial_y);
	virtual ~Point();
	void draw(cairo_t* cr);
};

#endif /* SRC_MODEL_POINT_H_ */
