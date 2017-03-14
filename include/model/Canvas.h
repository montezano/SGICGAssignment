#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <gtk/gtk.h>
#include <vector>
#include <cstring>


#include "util/Vector.h"
#include "model/Line.h"
#include "model/Point.h"
#include "model/Polygon.h"


class Canvas
{
public:
	Canvas(cairo_surface_t *surface);
	virtual ~Canvas();
	void addLine(const gchar* nome, Vector inicial, Vector final);
	void addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords);
	void addPoint(const gchar *nome, Vector init_position);
	void drawCanvas();
	void deleteDrawable(const gchar* nome);

private:
	std::vector<Drawable*> _canvas;
	cairo_surface_t *_surface;

};

#endif //__CANVAS_H__
