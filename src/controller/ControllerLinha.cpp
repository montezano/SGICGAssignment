#include "controller/ControllerLinha.h"

ControllerLinha::ControllerLinha(GtkBuilder * builder)
{
	_window = new WindowLinha(GTK_WIDGET(gtk_builder_get_object(builder, "window_linha")));

	GtkButton *button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_linha"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_linha"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_linha_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

}

ControllerLinha::~ControllerLinha()
{
}

void ControllerLinha::display()
{
	_window->display();
}

void ControllerLinha::add_linha_cb(GtkWidget * window)
{
	WindowLinha::WinLinha w_line = _window->add_linha();
	g_print(w_line.nome);
	Line line = Line(w_line.nome, w_line.v_inicial, w_line.v_final);
	//g_print(linha.tipo);
	//ControllerMainWindow * c;
	//c->addItemListView(linha);

}

WindowLinha *ControllerLinha::_window;

Controller *ControllerLinha::_controller;
