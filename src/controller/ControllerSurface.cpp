#include "ControllerSurface.h"

ControllerSurface::ControllerSurface(GtkBuilder * builder, Canvas *canvas)

{
	_window = new WindowSurface(GTK_WIDGET(gtk_builder_get_object(builder, "window_surface")), &bspline);

	GtkButton* button;
	GtkRadioButton *radio_button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_surface"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_points1"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_coords_cb), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_surface"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_surface_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	_controller = Controller::getInstance();

	_radio_group = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_bezier"));
	assert(_radio_group);


	radio_button = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_bspline"));
	assert(radio_button);

	_canvas = canvas;

}

ControllerSurface::~ControllerSurface()
{
}

void ControllerSurface::display()
{
	_window->display();
}

void ControllerSurface::add_coords_cb(GtkWidget *window)
{
	GSList *toggle_button = gtk_radio_button_get_group(_radio_group);
	if (toggle_button)
	{
		do
		{
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button->data)))
			{
				break;
			}
		} while ((toggle_button = g_slist_next(toggle_button)) != NULL);
	}

	std::string button_name = gtk_button_get_label(GTK_BUTTON(toggle_button->data));

	if (button_name == "Bézier")
	{
		bspline = false;
	}
	else
	{
		if (button_name == "B-Spline")
		{
			bspline = true;
		}
	}

	_coords.push_back(_window->add_coords());
}


void ControllerSurface::add_surface_cb(GtkWidget *window)
{
	WindowSurface::WinSurface w_surface = _window->add_surface();

	_canvas->addSurface(w_surface.nome.c_str(), _coords, bspline);
	_coords.clear();
}

WindowSurface *ControllerSurface::_window = NULL;
std::vector<Vector*> ControllerSurface::_coords;
Controller *ControllerSurface::_controller = NULL;
Canvas *ControllerSurface::_canvas = NULL;
GtkRadioButton *ControllerSurface::_radio_group = NULL;
bool ControllerSurface::bspline = true;

