/*
 * Line.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_LINE_H_
#define SRC_MODEL_LINE_H_

#include "model/Drawable.h"


class Line : public Drawable {
public:
	Line(const gchar *nome, double inicial_x, double inicial_y, double final_x, double final_y);
	Line(const gchar *nome, Vector init_position, Vector final_position);
	virtual ~Line();
	virtual void draw(cairo_surface_t *surface);

private:
	Vector _final_position;
};

#endif /* SRC_MODEL_LINE_H_ */
