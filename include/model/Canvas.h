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
#include "Curve2.h"
#include "Transformation.h"
#include "Windowport.h"


class Canvas : public Subject, public Observer
{
public:
	Canvas(Viewport *viewport, Windowport *window);
	Canvas();
	virtual ~Canvas();
	void setWindow(Windowport *window);
	void addLine(const gchar* nome, Vector *inicial, Vector *final);
	void addPolygon(const gchar *nome, std::vector<Vector*> coords, bool fill);
	void addCurve2(const gchar *nome, std::vector<Vector*> points, bool type);
	void addPoint(const gchar *nome, Vector *init_position);
	void drawCanvas(cairo_surface_t *surfac);
	void updateWindow();
	void deleteDrawable(const gchar *nome);
	void translateDrawable(const gchar* name, Vector &offset);
	void scaleDrawable(const gchar *name, Vector factor);
	void rotateDrawableOwnCenter(const gchar *name, Vector &angle);
	void rotateDrawableSpecificCenter(const gchar *name, Vector &angle, Vector center);
	void rotateDrawableWorldCenter(const gchar *name, Vector &angle);

	virtual void onNotify(void *data, Events event);
private:

	Drawable *findDrawable(const gchar *name);
	std::vector<Drawable*> _canvas;
	Viewport *_viewport;	// DO NOT FREE
	Windowport *_window;	// DO NOT FREE

	Line *_guideline_z, *_guideline_y, *_guideline_x;
};

#endif //__CANVAS_H__
