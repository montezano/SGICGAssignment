#include "view/Window.h"

Window::Window(GtkWidget * window)
{
	assert(window);
	_window = window;
	gtk_window_set_position(GTK_WINDOW(_window), GTK_WIN_POS_CENTER_ALWAYS);
}

Window::~Window()
{
	gtk_widget_destroy(_window);
}

void Window::display()
{
	gtk_widget_show(_window);
}

void Window::setWindow(GtkWidget * window)
{
	assert(window);
	_window = window;
}

GtkWidget * Window::getWindow()
{
	return _window;
}
