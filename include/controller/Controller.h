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
#include "Clipping.h"


using namespace std;

class Controller : public Observer
{
	friend class ControllerMainWindow;
	friend class ControllerLinha;
	friend class ControllerPonto;
	friend class ControllerPoligono;
public:

	enum ClippingAlgorithm
	{
		POINT,
		CS,
		LB,
		NICLEENIC,
		SUTHHODG,
		WEIL
	};

	void operator=(Controller const&) = delete;
	~Controller();

	static Controller *getInstance();
	static Controller *initialize(int argc, char *argv[]);
	static void start();
	static void setAlgorithm(ClippingAlgorithm alg);


	void onNotify(void *data, Events event);


private:
	Controller(int argc, char *argv[]);

	void configureObservers();
	void initClippingAlgorithm();

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
	static Command *_point_clipping;
	static Command *_line_clipping;
	static Command *_polygon_clipping;
	Windowport _windowport;
	
};

#endif//__CONTROLLER_H__
