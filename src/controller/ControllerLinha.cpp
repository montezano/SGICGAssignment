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
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

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
	WindowLinha::Linha linha;
	linha = _window->add_linha();
	//LUIZ, aqui você pega os valores do struct linha para fazer o que quiser. Estão como tipos primitivos do gtk (gchar, gchar, gint, gint)
	//O viewport fará parte do modelo, e acredito que será chamado a partir do controle.
}

WindowLinha *ControllerLinha::_window;

Controller *ControllerLinha::_controller;