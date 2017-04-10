#include "ControllerPoligono.h"

ControllerPoligono::ControllerPoligono(GtkBuilder * builder, Canvas *canvas)

{
	_window = new WindowPoligono(GTK_WIDGET(gtk_builder_get_object(builder, "window_poligono")));

	GtkButton* button;
	GtkRadioButton *radio_button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel_poligon"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_coordinates"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_coords_cb), _window->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ok_poligon"));
	assert(button);
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(add_poligono_cb), _window->getWindow());

	g_signal_connect(_window->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	_controller = Controller::getInstance();

	_radio_group = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_polygon_frame"));
	assert(_radio_group);


	radio_button = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_polygon_fill"));
	assert(radio_button);

	_canvas = canvas;

}

ControllerPoligono::~ControllerPoligono()
{
}

void ControllerPoligono::display()
{
	_window->display();
}

void ControllerPoligono::add_coords_cb(GtkWidget *window)
{
	_coords.push_back(_window->add_coords());
}


void ControllerPoligono::add_poligono_cb(GtkWidget *window)
{
	WindowPoligono::WinPoligono w_pol = _window->add_poligono();

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

	bool fill = false;
	if (button_name == "Arame")
	{
		fill = false;
	}
	else
	{
		if (button_name == "Preenchido")
		{
			fill = true;
		}
	}

	_canvas->addPolygon(w_pol.nome.c_str(), _coords, fill);
	_coords.clear();
}

WindowPoligono *ControllerPoligono::_window = NULL;
std::vector<Vector> ControllerPoligono::_coords;
Controller *ControllerPoligono::_controller = NULL;
Canvas *ControllerPoligono::_canvas = NULL;
GtkRadioButton *ControllerPoligono::_radio_group = NULL;

