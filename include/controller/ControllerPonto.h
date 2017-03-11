#ifndef __CONTROLERPONTO_H__
#define __CONTROLERPONTO_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/WindowPonto.h"
#include "controller/Controller.h"

using namespace std;

class ControllerPonto
{
public:
	ControllerPonto(GtkBuilder *builder);
	virtual ~ControllerPonto();

	static void display();

private:

	static void add_ponto_cb(GtkWidget *window);

	static WindowPonto *_window;

	static Controller *_controller;

};

#endif//__CONTROLERPONTO_H__