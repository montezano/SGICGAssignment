/*
 * Point.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_POINT_H_
#define SRC_MODEL_POINT_H_

#include "Drawable.h"
#include <gtk/gtk.h>

class Point : public Drawable {

public:
	Point(const gchar *nome, gdouble inicial_x, gdouble inicial_, Windowport *windowy);
	Point(const gchar *nome, Vector init_position, Windowport *window);
	virtual ~Point();
	virtual void draw(cairo_t *_cr, Viewport *viewport);
	virtual Vector getCenter();
	virtual void transform(Transformation &transformation);

protected:
	virtual void updateWindow();
};

#endif /* SRC_MODEL_POINT_H_ */
