#ifndef __CONTROLERLINHA_H__
#define __CONTROLERLINHA_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/Window.h"
#include "view/WindowLinha.h"
#include "controller/Controller.h"

using namespace std;

class ControllerLinha
{
public:

	ControllerLinha(GtkBuilder *builder);
	virtual ~ControllerLinha();

	static void display();

private:

	static void add_linha_cb(GtkWidget *window);
	static WindowLinha *_window;
	static Controller *_controller;

};

#endif//__CONTROLERLINHA_H__
