#pragma once
#ifndef __CONTROLERMAINWINDOW_H__
#define __CONTROLERMAINWINDOW_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "Window.h"
#include "MainWindow.h"
#include "Controller.h"
#include "Drawable.h"
#include "Canvas.h"
#include "Viewport.h"
using namespace std;

class ControllerMainWindow
{
public:
	ControllerMainWindow(GtkBuilder *builder, const Controller *controller, Canvas *canvas, Viewport *viewport);

	~ControllerMainWindow();

	void display();

	void initialize();

	Window *getWindow();
private:

	void configureButtons(GtkBuilder *builder);

	static void input_ponto_cb();
	static void input_poligono_cb();
	static void input_linha_cb();
	static void remove_object();
	static void moveUp();
	static void moveDown();
	static void moveLeft();
	static void moveRight();
	static void zoomIn();
	static void zoomOut();

	static gboolean draw_cb(GtkWidget *widget, cairo_t   *cr, gpointer   data);
	static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data);

	static MainWindow *_window;
	static GtkTreeView* _treeView;
	static const Controller *_controller;
	static Canvas *_canvas;
	static Viewport *_viewport;

};

#endif//__CONTROLERMAINWINDOW_H__
