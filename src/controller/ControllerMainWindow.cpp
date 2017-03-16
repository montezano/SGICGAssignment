#include "controller/ControllerMainWindow.h"

ControllerMainWindow::ControllerMainWindow(GtkBuilder * builder)
{

	_window = new MainWindow(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")));
	assert(_window);

	_controller = Controller::getInstance();
	assert(_controller);

	GtkButton* button;
	GtkToolButton* toolButton;

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

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_cima"));
	assert(toolButton);
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveUp), NULL);
		
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_baixo"));
	assert(toolButton);
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveDown), NULL);
		
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_esquerda"));
	assert(toolButton);
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveLeft), NULL);
		
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_direita"));
	assert(toolButton);
	g_signal_connect(toolButton, "clicked", G_CALLBACK(moveRight), NULL);
		
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_zoom_in"));
	assert(toolButton);
	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomIn), NULL);
		
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_zoom_out"));
	assert(toolButton);
	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomOut), NULL);

	_window->getViewport()->addObserver(_controller->_log);

	_canvas = new Canvas(_window->getViewport());
	_canvas->addObserver(static_cast<Observer*>(_window));
	assert(_controller->_log);
	_canvas->addObserver(static_cast<Observer*>(_controller->_log));

	g_signal_connect(_window->getDrawingArea(), "configure-event", G_CALLBACK(configure_event_cb), NULL);
	g_signal_connect(_window->getDrawingArea(), "draw", G_CALLBACK(draw_cb), NULL);

	_treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "object_list_treeview"));
	



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

Canvas * ControllerMainWindow::getCanvas()
{
	return _canvas;
}




///////////////////////////////////////////////////////////////////////
//	CALLBACK FUNCTIONS
///////////////////////////////////////////////////////////////////////
void ControllerMainWindow::moveUp(){
	_window->getViewport()->moveVertical(0.1);
	//_canvas->drawCanvas(_window->getSurface());
	//gtk_widget_queue_draw(GTK_WIDGET(_window->getDrawingArea()));
}

void ControllerMainWindow::moveDown(){
	_window->getViewport()->moveVertical(-0.1);
	//gtk_widget_queue_draw(GTK_WIDGET(_window->getDrawingArea()));
}

void ControllerMainWindow::moveLeft(){
	_window->getViewport()->moveHorizontal(-0.1);
	//gtk_widget_queue_draw(GTK_WIDGET(_window->getDrawingArea()));
}

void ControllerMainWindow::moveRight(){
	_window->getViewport()->moveHorizontal(0.1);
	//gtk_widget_queue_draw(GTK_WIDGET(_window->getDrawingArea()));
}

void ControllerMainWindow::zoomIn(){
	_window->getViewport()->zoom(1.25);
	//gtk_widget_queue_draw(GTK_WIDGET(_window->getDrawingArea()));
}

void ControllerMainWindow::zoomOut(){
	_window->getViewport()->zoom(0.8);
	//gtk_widget_queue_draw(GTK_WIDGET(_window->getDrawingArea()));
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
Controller *ControllerMainWindow::_controller = NULL;
Canvas *ControllerMainWindow::_canvas = NULL;
GtkTreeView* ControllerMainWindow::_treeView = NULL;
