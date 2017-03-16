#ifndef __CONTROLERPONTO_H__
#define __CONTROLERPONTO_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/WindowPonto.h"
#include "view/Window.h"
#include "model/Point.h"
#include "model/Canvas.h"
#include "controller/Controller.h"

using namespace std;

class ControllerPonto
{
public:
	ControllerPonto(GtkBuilder *builder, Canvas *canvas);
	virtual ~ControllerPonto();

	static void display();

private:

	static void add_ponto_cb(GtkWidget *window);

	static WindowPonto *_window;
	static Canvas *_canvas;


};

#endif//__CONTROLERPONTO_H__
