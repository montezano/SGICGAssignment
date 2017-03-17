/*
 * Line.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_LINE_H_
#define SRC_MODEL_LINE_H_

#include "Drawable.h"


class Line : public Drawable {
public:
	Line(const gchar *nome, float inicial_x, float inicial_y, float final_x, float final_y);
	Line(const gchar *nome, Vector init_position, Vector final_position);
	virtual ~Line();
	virtual void draw(cairo_t *_cr, Viewport *viewport);

private:
	Vector _final_position;
};

#endif /* SRC_MODEL_LINE_H_ */
