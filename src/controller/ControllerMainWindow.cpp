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

	button = GTK_BUTTON(gtk_builder_get_object(builder, "buttom_remove_object"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(remove_object), NULL);

	g_signal_connect(_window->getDrawingArea(), "configure-event", G_CALLBACK(configure_event_cb), NULL);


	g_signal_connect(_window->getDrawingArea(), "draw", G_CALLBACK(draw_cb), NULL);

	_treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "object_list_treeview"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));

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
	//drawable->draw(_window->getSurface());
	_canvas->drawCanvas();
}

void ControllerMainWindow::initialize()
{
}

Canvas * ControllerMainWindow::getCanvas()
{
	return _canvas;
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

void ControllerMainWindow::remove_object(){
	GtkTreeSelection *selection;
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(_treeView));
	if (gtk_tree_selection_get_selected(selection, &_model, &_iter)){
	 const gchar *name;
	 gtk_tree_model_get (_model, &_iter, 0, &name, -1);
	 g_print ("selected row is: %s\n", name);
	 _canvas->deleteDrawable(name);
 }else {
	 g_print ("no row selected.\n");
 }

}

void ControllerMainWindow::addItemListView(const gchar* nome, const gchar* tipo)
{
	gtk_list_store_append(GTK_LIST_STORE(_model), &_iter);
	gtk_list_store_set(GTK_LIST_STORE(_model),
												&_iter,
												0,
												nome,
												1,
												tipo,
												-1);
	gtk_tree_view_set_model(GTK_TREE_VIEW(_treeView),
														 _model);

}

void ControllerMainWindow::input_linha_cb()
{
	g_print("linha\n");
	_controller->_window_linha_controller->display();
}

gboolean ControllerMainWindow::draw_cb(GtkWidget * widget, cairo_t * cr, gpointer data)
{
	_canvas->drawCanvas();
	return _window->draw_window(widget, cr, data);
}

gboolean ControllerMainWindow::configure_event_cb(GtkWidget * widget, GdkEventConfigure * event, gpointer data)
{
	gboolean ret = _window->configure_event(widget, event, data);
	_canvas = new Canvas(_window->getSurface());

	return ret;
}

MainWindow *ControllerMainWindow::_window = NULL;
Controller *ControllerMainWindow::_controller = NULL;
Canvas *ControllerMainWindow::_canvas = NULL;
GtkTreeModel* ControllerMainWindow::_model = NULL;
GtkTreeIter ControllerMainWindow::_iter;
GtkTreeView* ControllerMainWindow::_treeView = NULL;
