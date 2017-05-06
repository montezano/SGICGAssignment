#include "MainWindow.h"

MainWindow::MainWindow(GtkWidget *window) :
	Window(window)
{
	_drawing_area = GTK_DRAWING_AREA(find_child(_window, "mainwindow_drawing_area"));
	assert(_drawing_area);

	_treeView = GTK_TREE_VIEW(find_child(_window, "treeview_object_list"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));

	//_tree_view = GTK_TREE_VIEW(find_child(_window, "treeview_main_object_list"));
	_surface = NULL;

	reconfigure(_window);
	
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

void MainWindow::onNotify(void *data, Events event)
{
	switch (event)
	{
	case Events::ADD_DRAWABLE:
	g_print("add drawable\n");
		gtk_list_store_append(GTK_LIST_STORE(_model), &_iter);
		gtk_list_store_set(GTK_LIST_STORE(_model),
			&_iter,
			0,
			static_cast<Drawable*>(data)->getNome(),
			1,
			static_cast<Drawable*>(data)->getTipo(),
			-1);
		gtk_tree_view_set_model(GTK_TREE_VIEW(_treeView),
			_model);
		reconfigure(GTK_WIDGET(_drawing_area));

		break;
	case Events::REMOVE_DRAWABLE:
		reconfigure(GTK_WIDGET(_drawing_area));

		break;
	case Events::WINDOW_MOVE:
	case Events::WINDOW_ZOOM:
	case Events::WINDOW_ROTATE:
		reconfigure(GTK_WIDGET(_drawing_area));
		break;
	case Events::TRANSFORMATION_TRANSLATE:
	case Events::TRANSFORMATION_SCALE:
	case Events::TRANSFORMATION_ROTATE:
		reconfigure(GTK_WIDGET(_drawing_area));
	}
}
//void MainWindow::deleteItem(GtkTreeModel *model, GtkTreeIter *iter){
//}
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
	return reconfigure(widget);
}

gboolean MainWindow::reconfigure(GtkWidget *widget)
{
	Vector *size = new Vector(static_cast<float>(gtk_widget_get_allocated_width(widget)),
		static_cast<float>(gtk_widget_get_allocated_height(widget)),0);

	notify(static_cast<void*>(size), Events::MAINWINDOW_RECONFIGURE);

	if (_surface)
	{
		cairo_surface_destroy(_surface);
	}


	_surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget),
		CAIRO_CONTENT_COLOR,
		gtk_widget_get_allocated_width(widget),
		gtk_widget_get_allocated_height(widget));
	clear_surface();


	//	cairo_t *cr;

	//cr = cairo_create(_surface);
	//	gtk_widget_draw((GtkWidget*)_drawing_area,cr);
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
