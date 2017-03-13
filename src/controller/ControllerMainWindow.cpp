#include "controller/ControllerMainWindow.h"

ControllerMainWindow::ControllerMainWindow(GtkBuilder * builder)
{

	_window = new MainWindow(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")));
	assert(_window);

	_controller = Controller::getInstance();
	assert(_controller);

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ponto"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(input_ponto_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_linha"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(input_linha_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_poligono"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(input_poligono_cb), NULL);


	g_signal_connect(_window->getDrawingArea(), "configure-event", G_CALLBACK(configure_event_cb), NULL);


	g_signal_connect(_window->getDrawingArea(), "draw", G_CALLBACK(draw_cb), NULL);

	_canvas = new Canvas();

//	GtkTreeIter    iter;
//	GtkTreeModel *model;
//	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));
//	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
//	gtk_list_store_set(GTK_LIST_STORE(model),
//	                      &iter,
//	                      0,
//	                      "John",
//	                      1,
//	                      "Doe",
//	                      2,
//	                      "Somewhere",
//	                      3,
//	                      "KS",
//	                      -1);
//	gtk_tree_view_set_model(GTK_TREE_VIEW(treeView),
//	                           model);

}

ControllerMainWindow::~ControllerMainWindow()
{
}

void ControllerMainWindow::display()
{
	_window->display();
}

void ControllerMainWindow::draw_drawable(Drawable * drawable)
{
	assert(drawable);
	drawable->draw(_window->getSurface());
}




///////////////////////////////////////////////////////////////////////
//	CALLBACK FUNCTIONS
///////////////////////////////////////////////////////////////////////

void ControllerMainWindow::input_ponto_cb()
{
	g_print("ponto\n");
	_controller->_window_ponto_controller->display();
}

void ControllerMainWindow::input_poligono_cb()
{
	g_print("poligono\n");
	_controller->_window_poligono_controller->display();
}


//void ControllerMainWindow::addItemListView(WindowLinha::Linha linha)
//{
//
//
//}

void ControllerMainWindow::input_linha_cb()
{
	g_print("linha\n");
	_controller->_window_linha_controller->display();
}

gboolean ControllerMainWindow::draw_cb(GtkWidget * widget, cairo_t * cr, gpointer data)
{
	return _window->draw_window(widget, cr, data);
}

gboolean ControllerMainWindow::configure_event_cb(GtkWidget * widget, GdkEventConfigure * event, gpointer data)
{
	return _window->configure_event(widget, event, data);
}

MainWindow *ControllerMainWindow::_window = NULL;
Controller *ControllerMainWindow::_controller = NULL;
Canvas *ControllerMainWindow::_canvas = NULL;
