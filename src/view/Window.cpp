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

GtkWidget *Window::find_child(GtkWidget* parent, const gchar* name)
{
	if (strcmp(g_utf8_casefold(gtk_widget_get_name((GtkWidget*)parent), -1), (gchar*)name) == 0) {
		return parent;
	}

	if (GTK_IS_BIN(parent)) {
		GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
		return find_child(child, name);
	}

	if (GTK_IS_CONTAINER(parent)) {
		GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
			do
			{
				GtkWidget* widget = find_child(GTK_WIDGET(children->data), name);
				if (widget != NULL) {
					return widget;
				}
			} while ((children = g_list_next(children)) != NULL);
		
		 
	}
	g_print("haven't found something\n");
	return NULL;
}