#include "controller/ControllerPonto.h"

ControllerPonto::ControllerPonto(GtkBuilder * builder)
{
	_window = new WindowPonto(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")));
	_controller = Controller::getInstance();

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_ponto"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_ponto"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_ponto_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

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
	WindowPonto::Ponto ponto;
	ponto = _window->add_ponto();
	//LUIZ, aqui você pega os valores do struct linha para fazer o que quiser. Estão como tipos primitivos do gtk (gchar, gchar, gint, gint)
	//O viewport fará parte do modelo, e acredito que será chamado a partir do controle.
}

WindowPonto *ControllerPonto::_window;
Controller *ControllerPonto::_controller = NULL;