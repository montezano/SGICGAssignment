#include "controller/ControllerMainWindow.h"

ControllerMainWindow::ControllerMainWindow(GtkBuilder * builder, const Controller *controller)
{

	_window = new MainWindow(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")), &_viewport);
	assert(_window);

	assert(controller);
	_controller = controller;

	configureButtons(builder);
	
	_canvas = new Canvas(&_viewport);

	g_signal_connect(_window->getDrawingArea(), "configure-event", G_CALLBACK(configure_event_cb), NULL);
	g_signal_connect(_window->getDrawingArea(), "draw", G_CALLBACK(draw_cb), NULL);

	_treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "object_list_treeview"));

	configureObservers();
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
	//_canvas->drawCanvas();
}

void ControllerMainWindow::initialize()
{
}

void ControllerMainWindow::configureObservers()
{
	_canvas->addObserver(_window);
	_canvas->addObserver(_controller->_log);

	_viewport.addObserver(_window);
	_viewport.addObserver(_controller->_log);
}

Canvas * ControllerMainWindow::getCanvas()
{
	return _canvas;
}


void ControllerMainWindow::configureButtons(GtkBuilder *builder)
{
	GtkButton* button;
	GtkToolButton* toolButton;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ponto"));
	g_signal_connect(button, "clicked", G_CALLBACK(input_ponto_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_linha"));
	g_signal_connect(button, "clicked", G_CALLBACK(input_linha_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_poligono"));
	g_signal_connect(button, "clicked", G_CALLBACK(input_poligono_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "buttom_remove_object"));
	g_signal_connect(button, "clicked", G_CALLBACK(remove_object), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_cima"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveUp), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_baixo"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveDown), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_esquerda"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveLeft), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_direita"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveRight), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_zoom_in"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomIn), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_zoom_out"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomOut), NULL);
}



///////////////////////////////////////////////////////////////////////
//	CALLBACK FUNCTIONS
///////////////////////////////////////////////////////////////////////
void ControllerMainWindow::moveUp(){
	_viewport.moveVertical(0.1);
}

void ControllerMainWindow::moveDown(){
	_viewport.moveVertical(-0.1);
}

void ControllerMainWindow::moveLeft(){
	_viewport.moveHorizontal(-0.1);
}

void ControllerMainWindow::moveRight(){
	_viewport.moveHorizontal(0.1);
}

void ControllerMainWindow::zoomIn(){
	_viewport.zoom(1.25);
}

void ControllerMainWindow::zoomOut(){
	_viewport.zoom(0.8);
}



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
	GtkTreeIter iter;	
	GtkTreeModel *model = NULL;
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(_treeView));
	if (gtk_tree_selection_get_selected(selection, &model, &iter)){
		const gchar *name;
		gtk_tree_model_get (model, &iter, 0, &name, -1);
		g_print ("selected row is: %s\n", name);
		_canvas->deleteDrawable(name);
		//_canvas->setSurface(_window->getSurface());
		gtk_list_store_remove (GTK_LIST_STORE(model), &iter);
				 
	 }else {
		 g_print ("no row selected.\n");
	 }
		
//	delete selection;
//	delete iter;
//	delete model;
}

void ControllerMainWindow::input_linha_cb()
{
	_controller->_window_linha_controller->display();
}

gboolean ControllerMainWindow::draw_cb(GtkWidget * widget, cairo_t * cr, gpointer data)
{
	_canvas->drawCanvas(_window->getSurface());
	return _window->draw_window(widget, cr, data);
}

gboolean ControllerMainWindow::configure_event_cb(GtkWidget * widget, GdkEventConfigure * event, gpointer data)
{
	gboolean ret = _window->configure_event(widget, event, data);
	return ret;
}

MainWindow *ControllerMainWindow::_window = NULL;
const Controller *ControllerMainWindow::_controller = NULL;
Canvas *ControllerMainWindow::_canvas = NULL;
GtkTreeView* ControllerMainWindow::_treeView = NULL;
Viewport ControllerMainWindow::_viewport;
