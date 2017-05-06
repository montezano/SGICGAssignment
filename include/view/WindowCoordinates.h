#ifndef __WINDOWCOORDINATES_H__
#define __WINDOWCOORDINATES_H__

#include "Window.h"
#include "Vector.h"

class WindowCoordinates : public Window
{
public:

	WindowCoordinates(GtkWidget *window);

	virtual void initialize();

	virtual void onNotify(void *data, Events event);

	Vector getCoordinates();

private:

	GtkSpinButton *_spinbutton_coordinates_x;
	GtkSpinButton *_spinbutton_coordinates_y;
	GtkSpinButton *_spinbutton_coordinates_z;


};
#endif // !__WINDOWCOORDINATES_H__
