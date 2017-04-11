#ifndef SRC_MODEL_POLYGON_H_
#define SRC_MODEL_POLYGON_H_

#include "Drawable.h"
#include <vector>

class Polygon : public Drawable {
public:
	Polygon(const gchar *nome, std::vector<Vector> coords, Windowport *window, bool fill);
	Polygon(const gchar *nome, Windowport *window);
	virtual ~Polygon() {}
	virtual void draw(cairo_t *_cr, Viewport *viewport);
	virtual Vector getCenter();
	virtual void transform(Transformation &transformation);
	virtual void updateWindow();

protected:
	virtual void clip();

	std::vector<Vector> _coords;
	std::vector<Vector> _coords_window;
	std::vector<Vector> _clipped_coords;

private:

	void CSClip(Vector &v_initial, Vector &v_final);
	unsigned int getCSRegion(Vector &vector);
	Vector clipCSLine(unsigned int &region, Vector &vector1, float coeficient);



	bool _fill;

};

#endif /* SRC_MODEL_LINE_H_ */
