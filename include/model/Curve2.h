#ifndef SRC_MODEL_CURVE2_H_
#define SRC_MODEL_CURVE2_H_

#include "Drawable.h"
#include "Polygon.h"
#include <vector>

class Curve2 : public Polygon {
public:
	Curve2(const gchar *nome, std::vector<Vector*> points, Windowport *window, bool type);
        Curve2(const gchar *nome, Windowport *window);
	virtual ~Curve2();  
	virtual void draw(cairo_t *_cr, Viewport *viewport);

        static const float _mbs[16];
private:
	void calcBezierCurve();
	void calcBSplineCurve();
	void prepareInitialDiferences();

	std::vector<Vector*> _points;
	float _rate;

	static const float _mb[4][4];
	static float _e[16];

};

#endif /* SRC_MODEL_LINE_H_ */
