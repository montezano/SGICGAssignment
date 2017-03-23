#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <gtk/gtk.h>
#include <vector>
#include <cstring>


#include "Vector.h"
#include "Subject.h"
#include "Line.h"
#include "Point.h"
#include "Polygon.h"
#include "Transformation.h"
#include "Windowport.h"


class Canvas : public Subject
{
public:
	Canvas(Viewport *viewport, Windowport *window);
	Canvas();
	virtual ~Canvas();
	void setWindow(Windowport *window);
	void addLine(const gchar* nome, Vector inicial, Vector final);
	void addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords);
	void addPoint(const gchar *nome, Vector init_position);
	void drawCanvas(cairo_surface_t *surfac);
	void updateViewport();
	void deleteDrawable(const gchar *nome);
	void translateDrawable(const gchar* name, Vector &offset);
	void scaleDrawable(const gchar *name, Vector factor);
	void rotateDrawableOwnCenter(const gchar *name, float angle);
	void rotateDrawableSpecificCenter(const gchar *name, float angle, Vector center);
	void rotateDrawableWorldCenter(const gchar *name, float angle);
	void updateWindowport();

private:

	Drawable *findDrawable(const gchar *name);
	std::vector<Drawable*> _canvas;
	Viewport *_viewport;
	Windowport *_window;

};

#endif //__CANVAS_H__
