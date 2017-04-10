#ifndef SRC_MODEL_LINE_H_
#define SRC_MODEL_LINE_H_

#include "Drawable.h"
#include <algorithm>

enum LineAlgorithm {
	CS,
	LB
};

extern LineAlgorithm _line_alg;

class Line : public Drawable {
public:
	Line(const gchar *nome, float inicial_x, float inicial_y, float final_x, float final_y, Windowport *window);
	Line(const gchar *nome, Vector init_position, Vector final_position, Windowport *window);
	virtual ~Line();
	virtual void draw(cairo_t *_cr, Viewport *viewport);
	virtual Vector getCenter();
	virtual void transform(Transformation &transformation);
	virtual void updateWindow();
	Vector getFinalPosition();
	Vector getFinalPositionWindow();


private:
	virtual void clip();
	void CSClip();
	void LBClip();
	unsigned int getCSRegion(Vector &vector);
	Vector clipCSLine(unsigned int &region, Vector &vector1, float coeficient);

	Vector _final_position;
	Vector _final_position_window;
	Vector _clipped_position;
	Vector _clipped_final_position;
};

#endif /* SRC_MODEL_LINE_H_ */
