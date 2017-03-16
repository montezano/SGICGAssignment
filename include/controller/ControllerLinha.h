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
#include "model/Line.h"
#include "model/Canvas.h"

using namespace std;

class ControllerLinha
{
public:

	ControllerLinha(GtkBuilder *builder, Canvas *canvas);
	virtual ~ControllerLinha();

	static void display();

private:

	static void add_linha_cb(GtkWidget *window);
	static WindowLinha *_window;
	static Canvas *_canvas;

};

#endif//__CONTROLERLINHA_H__
