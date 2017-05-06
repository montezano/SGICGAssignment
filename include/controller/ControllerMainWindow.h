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
#include "WindowCoordinates.h"
#include "Controller.h"
#include "Drawable.h"
#include "Canvas.h"
#include "Viewport.h"
#include "Line.h"

using namespace std;

class ControllerMainWindow
{
public:
	ControllerMainWindow(GtkBuilder *builder, const Controller *controller, Canvas *canvas, Viewport *viewport, Windowport *window);

	~ControllerMainWindow();

	void display();

	void initialize();

	Window *getWindow();
private:

	void configureButtons(GtkBuilder *builder);

	/////////////////////////////////
	/// CALLBACK FUNCTIONS
	/////////////////////////////////
	static void add_object_cb();
	static void remove_object();
	static void move_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static void zoom_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static void rotate_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static void translate_cb(GtkWidget *widget);
	static void point_algorithm_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static void line_algorithm_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static void polygon_algorithm_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);

	static gboolean rotate_object_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static void rotate_specific_cb();
	static gboolean scale_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data);
	static const gchar *getObjectSelected();
	static gboolean draw_cb(GtkWidget *widget, cairo_t   *cr, gpointer   data);
	static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data);


	/////////////////////////////////
	/// MEMBER VARIABLES
	/////////////////////////////////
	static MainWindow *_window;
	static WindowCoordinates *_window_coordinates;

	static GtkTreeView* _treeView;
	static const Controller *_controller;
	static Canvas *_canvas;
	static Viewport *_viewport;
	static Windowport *_windowport;

	static GtkRadioButton *_radio_button_linha;
	static GtkRadioButton *_radio_button_poligono;
	static GtkRadioButton *_radio_button_ponto;
	static GtkRadioButton *_radio_button_curve;


	static GtkRadioButton *_radio_button_rotation_world;
	static GtkRadioButton *_radio_button_rotation_self;
	static GtkRadioButton *_radio_button_rotation_specific;
	static GtkRadioButton *_radio_button_rotation_x;
	static GtkRadioButton *_radio_button_rotation_y;
	static GtkRadioButton *_radio_button_rotation_z;

	static GtkRadioMenuItem *_radio_menu_line;
	static GtkRadioMenuItem *_radio_menu_polygon;

	static GtkTreeSelection *selection;
	static GtkTreeIter iter;
	static GtkTreeModel *model;


};

#endif//__CONTROLERMAINWINDOW_H__
