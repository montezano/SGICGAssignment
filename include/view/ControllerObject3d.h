#ifndef __CONTROLEROBJECT3D_H__
#define __CONTROLEROBJECT3D_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "WindowObj3d.h"
#include "Controller.h"
#include "Vector.h"
#include "Object3D.h"
#include "Canvas.h"

using namespace std;

class ControllerObject3d
{
public:
	ControllerObject3d(GtkBuilder *builder, Canvas *canvas);
	virtual ~ControllerObject3d();

	static void display();

private:

	static void add_object3d_cb(GtkWidget *window);
	static void add_edges_cb(GtkWidget *window);

	static WindowObj3d *_window;
	static Controller *_controller;
	static std::vector<std::pair<Vector*, Vector*>> _edges;
	static Canvas *_canvas;

};

#endif//__CONTROLEROBJECT3D_H__
