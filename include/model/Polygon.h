/*
 * Line.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_POLYGON_H_
#define SRC_MODEL_POLYGON_H_

#include "model/Drawable.h"
#include <vector>

class Polygon : public Drawable {
public:
	Polygon(const gchar *nome, double inicial_x, double inicial_y, std::vector<Vector> coords);
	Polygon(const gchar *nome, Vector init_position, std::vector<Vector> coords);
	virtual ~Polygon();
	virtual void draw(cairo_t *_cr);

private:
	std::vector<Vector> _coords;
};

#endif /* SRC_MODEL_LINE_H_ */
