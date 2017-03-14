#ifndef __CONTROLERPOLIGONO_H__
#define __CONTROLERPOLIGONO_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/WindowPoligono.h"
#include "controller/Controller.h"
#include "util/Vector.h"
#include "model/Polygon.h"

using namespace std;

class ControllerPoligono
{
public:
	ControllerPoligono(GtkBuilder *builder);
	virtual ~ControllerPoligono();

	static void display();

private:

	static void add_poligono_cb(GtkWidget *window);
	static void add_coords_cb(GtkWidget *window);


	static WindowPoligono *_window;
	static Controller *_controller;
	static std::vector<Vector> _coords;

};

#endif//__CONTROLERPOLIGONO_H__
