#ifndef SRC_MODEL_CURVE2_H_
#define SRC_MODEL_CURVE2_H_

#include "Drawable.h"
#include "Polygon.h"
#include <vector>

class Curve2 : public Polygon {
public:
	Curve2(const gchar *nome, std::vector<Vector> points, Windowport *window);
	virtual ~Curve2() {}
	virtual void draw(cairo_t *_cr, Viewport *viewport);
	

private:
	void calculateCurve();


	std::vector<Vector> _points;
	float mb[4][4] = {{-1,3,-3,1}, {3,-6, 3, 0}, {-3, 3, 0, 0}, {1, 0, 0, 0}};
	std::vector<Vector> _curve_coords;
	std::vector<Vector> _curve_coords_window;
	std::vector<Vector> _clipped_curve;

};

#endif /* SRC_MODEL_LINE_H_ */
