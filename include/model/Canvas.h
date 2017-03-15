#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <gtk/gtk.h>
#include <vector>
#include <cstring>


#include "util/Vector.h"
#include "util/Subject.h"
#include "model/Line.h"
#include "model/Point.h"
#include "model/Polygon.h"


class Canvas : public Subject
{
public:
	Canvas(Viewport *viewport);
	Canvas(cairo_surface_t *surface);
	void setSurface(cairo_surface_t *surface);
	virtual ~Canvas();
	void addLine(const gchar* nome, Vector inicial, Vector final);
	void addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords);
	void addPoint(const gchar *nome, Vector init_position);
	void drawCanvas(cairo_t *cr);
	void updateViewport();
	void deleteDrawable(const gchar* nome);

private:
	std::vector<Drawable*> _canvas;
	cairo_surface_t *_surface;
	cairo_t *_cr;
	Viewport *_viewport;

};

#endif //__CANVAS_H__
