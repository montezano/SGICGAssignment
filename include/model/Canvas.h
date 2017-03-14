#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <gtk/gtk.h>
#include <vector>

#include "util/Vector.h"
#include "util/Subject.h"
#include "model/Line.h"

class Canvas : public Subject
{
public:
	Canvas(cairo_surface_t *surface);
	virtual ~Canvas();
	void addDrawable(Drawable* d);

	void drawCanvas();

private:
	std::vector<Drawable*> _canvas;
	cairo_surface_t *_surface;

};

#endif //__CANVAS_H__
