#pragma once
#ifndef __CONTROLERMAINWINDOW_H__
#define __CONTROLERMAINWINDOW_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/Window.h"
#include "view/MainWindow.h"
#include "controller/Controller.h"
#include "model/Drawable.h"
#include "model/Canvas.h"

using namespace std;

class ControllerMainWindow
{
public:
	ControllerMainWindow(GtkBuilder *builder);

	~ControllerMainWindow();

	void display();

	void draw_drawable(Drawable *drawable);
	void addItemListView(Drawable * drawable);
	void initialize();

	Canvas *getCanvas();
private:

	static void input_ponto_cb();
	static void input_poligono_cb();
	static void input_linha_cb();
	static gboolean draw_cb(GtkWidget *widget, cairo_t   *cr, gpointer   data);
	static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data);

	static MainWindow *_window;
	GtkTreeView* _treeView;
	GtkTreeIter    _iter;
	GtkTreeModel *_model;
	static Controller *_controller;
	static Canvas *_canvas;


};

#endif//__CONTROLERMAINWINDOW_H__
