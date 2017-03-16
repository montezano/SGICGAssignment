#include "controller/ControllerPonto.h"

ControllerPonto::ControllerPonto(GtkBuilder * builder, Canvas *canvas)
{
	_window = new WindowPonto(GTK_WIDGET(gtk_builder_get_object(builder, "window_ponto")));

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_ponto"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_ponto"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_ponto_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	_canvas = canvas;
}

ControllerPonto::~ControllerPonto()
{
}

void ControllerPonto::display()
{
	_window->display();
}

void ControllerPonto::add_ponto_cb(GtkWidget *window)
{
	WindowPonto::WinPonto w_ponto = _window->add_ponto();
	_canvas->addPoint(w_ponto.nome.c_str(),w_ponto.v_inicial);

}

WindowPonto *ControllerPonto::_window;
Canvas *ControllerPonto::_canvas = NULL;
