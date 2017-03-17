#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>

#include <assert.h>

#include "Window.h"
#include "Drawable.h"

class MainWindow : public Window
{
public:

	MainWindow(GtkWidget *window, Viewport *viewport);
	virtual ~MainWindow();

	void initialize();
	GtkDrawingArea* getDrawingArea();
	cairo_surface_t *getSurface();

	gboolean draw_window(GtkWidget *widget, cairo_t   *cr, gpointer   data);
	gboolean configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data);

	virtual void onNotify(void *data, Events event);
	gboolean reconfigure(GtkWidget *widget);
		
private:

//	gboolean reconfigure(GtkWidget *widget);
	void clear_surface();

	GtkTreeView* _tree_view;
	GtkDrawingArea* _drawing_area;
	cairo_surface_t *_surface;

	GtkTreeView* _treeView;
	GtkTreeIter    _iter;
	GtkTreeModel *_model;

};


#endif //__MAINWINDOW_H__
