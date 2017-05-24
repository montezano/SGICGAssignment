#ifndef __CONTROLERSURFACE_H__
#define __CONTROLERSURFACE_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "WindowSurface.h"
#include "Controller.h"
#include "Vector.h"
#include "Surface.h"
#include "Canvas.h"

using namespace std;

class ControllerSurface
{
public:
	ControllerSurface(GtkBuilder *builder, Canvas *canvas);
	virtual ~ControllerSurface();

	static void display();

private:

	static void add_surface_cb(GtkWidget *window);
	static void add_coords_cb(GtkWidget *window);

	static WindowSurface *_window;
	static Controller *_controller;
	static std::vector<Vector*> _coords;
	static std::vector<std::vector<Vector*>> _matrix;
	static Canvas *_canvas;
	static GtkRadioButton *_radio_group;
	static bool bspline;


};

#endif//__CONTROLERBESIER_H__
