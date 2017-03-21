#ifndef __CONTROLERPOLIGONO_H__
#define __CONTROLERPOLIGONO_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "WindowPoligono.h"
#include "Controller.h"
#include "Vector.h"
#include "Polygon.h"
#include "Canvas.h"

using namespace std;

class ControllerPoligono
{
public:
	ControllerPoligono(GtkBuilder *builder, Canvas *canvas);
	virtual ~ControllerPoligono();

	static void display();

private:

	static void add_poligono_cb(GtkWidget *window);
	static void add_coords_cb(GtkWidget *window);


	static WindowPoligono *_window;
	static Controller *_controller;
	static std::vector<Vector> _coords;
	static Canvas *_canvas;

};

#endif//__CONTROLERPOLIGONO_H__
