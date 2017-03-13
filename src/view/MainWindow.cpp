#include "view/MainWindow.h"

MainWindow::MainWindow(GtkWidget *window) :
	Window(window)
{
	_drawing_area = GTK_DRAWING_AREA(find_child(_window, "mainwindow_drawing_area"));
	assert(_drawing_area);
	//_tree_view = GTK_TREE_VIEW(find_child(_window, "treeview_main_object_list"));
	_surface = NULL;
	g_print("MainWindow build\n");
}

MainWindow::~MainWindow()
{
	cairo_surface_destroy(_surface);
}

void MainWindow::initialize()
{
}

GtkDrawingArea * MainWindow::getDrawingArea()
{
	return _drawing_area;
}

cairo_surface_t * MainWindow::getSurface()
{
	return _surface;
}

void MainWindow::onNotify(Events event)
{
}

gboolean MainWindow::draw_window(GtkWidget *widget, cairo_t   *cr, gpointer   data)
{
	assert(cr);
	cairo_set_source_surface(cr, _surface, 0, 0);
	cairo_paint(cr);
	gtk_widget_queue_draw(_window);


	return FALSE;
}

gboolean MainWindow::configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
	if (_surface)
	{
		cairo_surface_destroy(_surface);
	}


	_surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
		CAIRO_CONTENT_COLOR,
		gtk_widget_get_allocated_width(widget),
		gtk_widget_get_allocated_height(widget));
	clear_surface();
	return TRUE;
}

void MainWindow::clear_surface()
{
	cairo_t *cr;

	cr = cairo_create(_surface);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_paint(cr);

	cairo_destroy(cr);
}
