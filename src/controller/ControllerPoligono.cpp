#include "controller/ControllerPoligono.h"

ControllerPoligono::ControllerPoligono(GtkBuilder * builder, Canvas *canvas)

{
	_window = new WindowPoligono(GTK_WIDGET(gtk_builder_get_object(builder, "window_poligono")));

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_poligono"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_coordinates"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_coords_cb), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_poligono"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_poligono_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	_controller = Controller::getInstance();

	_canvas = canvas;

}

ControllerPoligono::~ControllerPoligono()
{
}

void ControllerPoligono::display()
{
	_window->display();
}

void ControllerPoligono::add_coords_cb(GtkWidget *window)
{
	_coords.push_back(_window->add_coords());
}
void ControllerPoligono::add_poligono_cb(GtkWidget *window)
{
	WindowPoligono::WinPoligono w_pol = _window->add_poligono();
	_canvas->addPolygon(w_pol.nome.c_str(), _coords[0], _coords);
}

WindowPoligono *ControllerPoligono::_window = NULL;
std::vector<Vector> ControllerPoligono::_coords;
Controller *ControllerPoligono::_controller = NULL;
Canvas *ControllerPoligono::_canvas = NULL;
