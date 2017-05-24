#include "ControllerObject3d.h"

ControllerObject3d::ControllerObject3d(GtkBuilder * builder, Canvas *canvas)

{
	_window = new WindowObj3d(GTK_WIDGET(gtk_builder_get_object(builder, "window_object3d")));

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_obj3d"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_edges"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_edges_cb), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_obj3d"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_object3d_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	_controller = Controller::getInstance();

	_canvas = canvas;

}

ControllerObject3d::~ControllerObject3d()
{
}

void ControllerObject3d::display()
{
	_window->display();
}

void ControllerObject3d::add_edges_cb(GtkWidget *window)
{
	_edges.push_back(_window->add_edge());
}


void ControllerObject3d::add_object3d_cb(GtkWidget *window)
{
	std::string obj_name = _window->add_object3d();
	
	_canvas->addObject3D(obj_name.c_str(), _edges);
	_edges.clear();
}

WindowObj3d *ControllerObject3d::_window = NULL;
std::vector<std::pair<Vector*, Vector*>> ControllerObject3d::_edges;
Controller *ControllerObject3d::_controller = NULL;
Canvas *ControllerObject3d::_canvas = NULL;

