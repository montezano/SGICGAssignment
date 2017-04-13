#ifndef __CONTROLERBESIER_H__
#define __CONTROLERBESIER_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "WindowBesier.h"
#include "Controller.h"
#include "Vector.h"
#include "Curve2.h"
#include "Canvas.h"

using namespace std;

class ControllerBesier
{
public:
	ControllerBesier(GtkBuilder *builder, Canvas *canvas);
	virtual ~ControllerBesier();

	static void display();

private:

	static void add_besier_cb(GtkWidget *window);
	static void add_coords_cb(GtkWidget *window);

	static WindowBesier *_window;
	static Controller *_controller;
	static std::vector<Vector> _coords;
	static Canvas *_canvas;

};

#endif//__CONTROLERBESIER_H__
