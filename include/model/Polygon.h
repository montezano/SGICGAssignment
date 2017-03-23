/*
 * Line.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_POLYGON_H_
#define SRC_MODEL_POLYGON_H_

#include "Drawable.h"
#include <vector>

class Polygon : public Drawable {
public:
	Polygon(const gchar *nome, double inicial_x, double inicial_y, std::vector<Vector> coords, Windowport *window);
	Polygon(const gchar *nome, Vector init_position, std::vector<Vector> coords, Windowport *window);
	virtual ~Polygon();
	virtual void draw(cairo_t *_cr, Viewport *viewport);
	virtual Vector getCenter();
	virtual void transform(Transformation &transformation);

protected:
	virtual void updateWindow();

private:
	std::vector<Vector> _coords;
	std::vector<Vector> _coords_window;
};

#endif /* SRC_MODEL_LINE_H_ */
