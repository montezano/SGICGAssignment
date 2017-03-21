#ifndef __CONTROLER_H__
#define __CONTROLER_H__

/////////////////////////////////
/// CONFIGURATIONS
/////////////////////////////////
#define MAIN_WINDOW_FILE "./ui/main_window.glade"

class ControllerMainWindow;
class ControllerLinha;
class ControllerPoligono;
class ControllerPonto;

/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "Window.h"
#include "ControllerMainWindow.h"
#include "ControllerLinha.h"
#include "ControllerPonto.h"
#include "ControllerPoligono.h"
#include "Canvas.h"
#include "Observer.h"
#include "Log.h"


using namespace std;

class Controller : public Observer
{
	friend class ControllerMainWindow;
	friend class ControllerLinha;
	friend class ControllerPonto;
	friend class ControllerPoligono;
public:

	void operator=(Controller const&) = delete;
	~Controller();

	static Controller *getInstance();
	static Controller *initialize(int argc, char *argv[]);
	static void start();

	void onNotify(void *data, Events event);


private:
	Controller(int argc, char *argv[]);

	void configureObservers();

	static GtkBuilder *_builder;

	static ControllerMainWindow *_main_window_controller;
	static ControllerLinha		*_window_linha_controller;
	static ControllerPonto		*_window_ponto_controller;
	static ControllerPoligono	*_window_poligono_controller;
	static bool _initialized;
	static Controller *_instance;
	static Viewport _viewport;
	static Log _log;
	static Canvas _canvas;
};

#endif//__CONTROLLER_H__
