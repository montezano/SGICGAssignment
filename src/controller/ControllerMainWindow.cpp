#include "controller/ControllerMainWindow.h"

ControllerMainWindow::ControllerMainWindow(GtkBuilder * builder, const Controller *controller, Canvas *canvas, Viewport *viewport)
{
	assert(viewport);
	_viewport = viewport;
	_window = new MainWindow(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")), _viewport);
	assert(_window);

	assert(controller);
	_controller = controller;

	configureButtons(builder);
	


	g_signal_connect(_window->getDrawingArea(), "configure-event", G_CALLBACK(configure_event_cb), NULL);
	g_signal_connect(_window->getDrawingArea(), "draw", G_CALLBACK(draw_cb), NULL);

	_treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "object_list_treeview"));

	_canvas = canvas;
}

ControllerMainWindow::~ControllerMainWindow()
{
}

void ControllerMainWindow::display()
{
	_window->display();
}

void ControllerMainWindow::initialize()
{
}

Window * ControllerMainWindow::getWindow()
{
	return _window;
}

void ControllerMainWindow::configureButtons(GtkBuilder *builder)
{
	GtkButton* button;
	GtkToolButton* toolButton;

	/////////////////////////////////
	/// ADD/REMOVE BUTTONS
	/////////////////////////////////
	_radio_button_linha = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_add_line"));

	_radio_button_poligono = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_add_polygon"));

	_radio_button_ponto = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_add_point"));

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_add_object"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(add_object_cb), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_remove_object"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(remove_object), NULL);

	/////////////////////////////////
	/// VIEWPORT BUTTONS
	/////////////////////////////////
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

	/////////////////////////////////
	/// TRANSOFRMATION BUTTONS
	/////////////////////////////////
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_up"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomOut), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_left"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomOut), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_down"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomOut), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_right"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(zoomOut), NULL);


}



///////////////////////////////////////////////////////////////////////
//	CALLBACK FUNCTIONS
///////////////////////////////////////////////////////////////////////
void ControllerMainWindow::moveUp(){
	_viewport->moveVertical(0.1);
}

void ControllerMainWindow::moveDown(){
	_viewport->moveVertical(-0.1);
}

void ControllerMainWindow::moveLeft(){
	_viewport->moveHorizontal(-0.1);
}

void ControllerMainWindow::moveRight(){
	_viewport->moveHorizontal(0.1);
}

void ControllerMainWindow::zoomIn(){
	_viewport->zoom(1.25);
}

void ControllerMainWindow::zoomOut(){
	_viewport->zoom(0.8);
}

void ControllerMainWindow::translate_up_cb()
{

}

void ControllerMainWindow::translate_left_cb()
{

}

void ControllerMainWindow::translate_right_cb()
{

}

void ControllerMainWindow::translate_down_cb()
{

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

void ControllerMainWindow::add_object_cb()
{
	GSList *toggle_button = gtk_radio_button_get_group(_radio_button_linha);
	int index = -1;
	if (toggle_button)
	{
		do
		{
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button->data)))
			{
				break;
			}
		} while ((toggle_button = g_slist_next(toggle_button)) != NULL);
	}

	GtkButton *button = GTK_BUTTON(toggle_button->data);
	std::string button_name = gtk_button_get_label(button);

	if(button_name == "Linha")
	{
		_controller->_window_linha_controller->display();
	}
	else
	{
		if (button_name == "Poligono")
		{
			_controller->_window_poligono_controller->display();
		}
		else
		{
			_controller->_window_ponto_controller->display();
		}
	}
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
Viewport *ControllerMainWindow::_viewport = NULL;
Canvas *ControllerMainWindow::_canvas = NULL;
GtkTreeView* ControllerMainWindow::_treeView = NULL;

GtkRadioButton *ControllerMainWindow::_radio_button_linha = NULL;
GtkRadioButton *ControllerMainWindow::_radio_button_poligono = NULL;
GtkRadioButton *ControllerMainWindow::_radio_button_ponto = NULL;