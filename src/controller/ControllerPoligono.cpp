#include "controller/ControllerPoligono.h"

ControllerPoligono::ControllerPoligono(GtkBuilder * builder)

{
	_window = new WindowPoligono(GTK_WIDGET(gtk_builder_get_object(builder, "window_poligono")));

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_poligono"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_poligono"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_poligono_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

}

ControllerPoligono::~ControllerPoligono()
{
}

void ControllerPoligono::display()
{
	_window->display();
}

void ControllerPoligono::add_poligono_cb(GtkWidget *window)
{
	WindowPoligono::Poligono poligono = _window->add_poligono();
	//LUIZ, aqui voc� pega os valores do struct linha para fazer o que quiser. Est�o como tipos primitivos do gtk (gchar, gchar, gint, gint)
	//O viewport far� parte do modelo, e acredito que ser� chamado a partir do controle.
}

WindowPoligono *ControllerPoligono::_window;
