#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <gtk/gtk.h>
#include <vector>
#include <cstring>


#include "util/Vector.h"
#include "util/Subject.h"
#include "Line.h"
#include "Point.h"
#include "Polygon.h"


class Canvas : public Subject
{
public:
	Canvas(Viewport *viewport);
	Canvas();
	virtual ~Canvas();
	void addLine(const gchar* nome, Vector inicial, Vector final);
	void addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords);
	void addPoint(const gchar *nome, Vector init_position);
	void drawCanvas(cairo_surface_t *surfac);
	void updateViewport();
	void deleteDrawable(const gchar* nome);

private:
	std::vector<Drawable*> _canvas;
	Viewport *_viewport;

};

#endif //__CANVAS_H__
