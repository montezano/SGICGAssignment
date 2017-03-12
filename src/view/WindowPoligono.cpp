#include "view/WindowPoligono.h"

WindowPoligono::WindowPoligono(GtkWidget * window) :
	Window(window)
{
	initialize();
}

void WindowPoligono::initialize()
{
}

WindowPoligono::Poligono WindowPoligono::add_poligono()
{

	WindowPoligono::Poligono poligono;
	poligono.nome = "blah";
	poligono.tipo = "linha";
	poligono.x = 0;
	poligono.y = 0;

	gtk_widget_hide(_window);
	return poligono;
}

void WindowPoligono::onNotify(Events event)
{
}
