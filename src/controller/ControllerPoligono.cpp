#include "controller/ControllerPoligono.h"

ControllerPoligono::ControllerPoligono(GtkBuilder * builder)

{
	_window = new WindowPoligono(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")));

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_ponto"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_ponto"));
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
	//LUIZ, aqui você pega os valores do struct linha para fazer o que quiser. Estão como tipos primitivos do gtk (gchar, gchar, gint, gint)
	//O viewport fará parte do modelo, e acredito que será chamado a partir do controle.
}

WindowPoligono *ControllerPoligono::_window;
