#include "ControllerBesier.h"

ControllerBesier::ControllerBesier(GtkBuilder * builder, Canvas *canvas)

{
	_window = new WindowBesier(GTK_WIDGET(gtk_builder_get_object(builder, "window_besier")));

	GtkButton* button;
	GtkRadioButton *radio_button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_besier"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_points"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_coords_cb), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_besier"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_besier_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	_controller = Controller::getInstance();

	_radio_group = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_bezier"));
	assert(_radio_group);


	radio_button = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_bspline"));
	assert(radio_button);

	_canvas = canvas;

}

ControllerBesier::~ControllerBesier()
{
}

void ControllerBesier::display()
{
	_window->display();
}

void ControllerBesier::add_coords_cb(GtkWidget *window)
{
	_coords.push_back(_window->add_coords());
}


void ControllerBesier::add_besier_cb(GtkWidget *window)
{
	WindowBesier::WinBesier w_besier = _window->add_besier();

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

	bool type = false;
	if (button_name == "Bézier")
	{
		type = false;
	}
	else
	{
		if (button_name == "B-Spline")
		{
			type = true;
		}
	}
	_canvas->addCurve2(w_besier.nome.c_str(), _coords,type);
	_coords.clear();
}

WindowBesier *ControllerBesier::_window = NULL;
std::vector<Vector*> ControllerBesier::_coords;
Controller *ControllerBesier::_controller = NULL;
Canvas *ControllerBesier::_canvas = NULL;
GtkRadioButton *ControllerBesier::_radio_group = NULL;
