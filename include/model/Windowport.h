#ifndef __WINDOWPORT_H__
#define __WINDOWPORT_H__

#include <gtk/gtk.h>
#include "Vector.h"
#include "Viewport.h"
#include "Transformation.h"
#include "Subject.h"

class Windowport : public Subject
{
public:
	Windowport(Vector min, Vector max, Viewport *viewport);

	void setSize(Vector vector);
	void setCenter(Vector position);
	void move(Vector offset);
	void rotate(Vector angles);
	void zoom(float factor);
	Transformation getTransformation();
	Vector *normalize(Vector *vector);
	float unormalize_x(Vector *vector);
	float unormalize_y(Vector *vector);
	Vector unormalize(Vector *vector);
	void draw(cairo_t *_cr, Viewport *viewport);

	Vector *getInitWindowPosition();
	Vector *getFinalWindowPosition();

private:
	Vector _center;
	Vector _size;
	Vector _initial_position;
	Vector _final_position;
	Vector _vrp, _vpn;
	Viewport *_viewport;
	Transformation _transformation;
};

#endif //__WINDOWPORT_H__
