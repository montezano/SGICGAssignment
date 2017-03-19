#include "WindowCoordinates.h"

WindowCoordinates::WindowCoordinates(GtkWidget * window) :
	Window(window)
{
	initialize();

	_spinbutton_coordinates_x = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_coordinates_x"));
	assert(_spinbutton_coordinates_x);

	_spinbutton_coordinates_y = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_coordinates_y"));
	assert(_spinbutton_coordinates_y);
        

}

void WindowCoordinates::initialize()
{
}

void WindowCoordinates::onNotify(void * data, Events event)
{
}

Vector WindowCoordinates::getCoordinates()
{
	return Vector(static_cast<float>(gtk_spin_button_get_value(_spinbutton_coordinates_x)),
		static_cast<float>(gtk_spin_button_get_value(_spinbutton_coordinates_y)));
}
