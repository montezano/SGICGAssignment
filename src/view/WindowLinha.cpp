#include "view/WindowLinha.h"

WindowLinha::WindowLinha(GtkWidget * window) :
	Window(window)
{
	initialize();
}

void WindowLinha::initialize()
{
}

WindowLinha::Linha WindowLinha::add_linha()
{

	WindowLinha::Linha linha;
	linha.nome = "blah";
	linha.tipo = "linha";
	linha.x = 0;
	linha.y = 0;

	gtk_widget_hide(_window);
	return linha;
}
