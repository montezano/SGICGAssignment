#include "ControllerBesier.h"

ControllerBesier::ControllerBesier(GtkBuilder * builder, Canvas *canvas)

{
	_window = new WindowBesier(GTK_WIDGET(gtk_builder_get_object(builder, "window_besier")));

	GtkButton* button;
	GtkRadioButton *radio_button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_besier"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_points"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_coords_cb), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_besier"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_besier_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	_controller = Controller::getInstance();

	_canvas = canvas;

}

ControllerBesier::~ControllerBesier()
{
}

void ControllerBesier::display()
{
	_window->display();
}

void ControllerBesier::add_coords_cb(GtkWidget *window)
{
	_coords.push_back(_window->add_coords());
}


void ControllerBesier::add_besier_cb(GtkWidget *window)
{
	WindowBesier::WinBesier w_besier = _window->add_besier();

	_canvas->addCurve2(w_besier.nome.c_str(), _coords);
	_coords.clear();
}

WindowBesier *ControllerBesier::_window = NULL;
std::vector<Vector> ControllerBesier::_coords;
Controller *ControllerBesier::_controller = NULL;
Canvas *ControllerBesier::_canvas = NULL;

