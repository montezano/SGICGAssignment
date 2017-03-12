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
	Line(const gchar *nome, const gchar *tipo, gdouble inicial_x, gdouble inicial_y, gdouble final_x, gdouble final_y);
	virtual ~Line();
	void draw(cairo_t* cr);

private:
	gdouble final_x;
	gdouble final_y;
};

#endif /* SRC_MODEL_LINE_H_ */
