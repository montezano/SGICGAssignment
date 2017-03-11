#include "view/WindowPonto.h"

WindowPonto::WindowPonto(GtkWidget * window) :
	Window(window)
{
	initialize();
}

void WindowPonto::initialize()
{
}

WindowPonto::Ponto WindowPonto::add_ponto()
{

	WindowPonto::Ponto ponto;
	ponto.nome = "blah";
	ponto.tipo = "linha";
	ponto.x = 0;
	ponto.y = 0;

	gtk_widget_hide(_window);
	return ponto;
}
