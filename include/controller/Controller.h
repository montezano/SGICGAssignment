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

#include "view/Window.h"
#include "controller/ControllerMainWindow.h"
#include "controller/ControllerLinha.h"
#include "controller/ControllerPonto.h"
#include "controller/ControllerPoligono.h"


using namespace std;

class Controller
{
	friend class ControllerMainWindow;
	friend class ControllerLinha;
	//friend class ControllerPonto;
	//friend class ControllerPoligono;
public:

	void operator=(Controller const&) = delete;
	~Controller();
	
	static Controller *getInstance();
	static Controller *initialize(int argc, char *argv[]);
	static void start();


private:
	Controller(int argc, char *argv[]);


	GtkBuilder *_builder;

	static ControllerMainWindow *_main_window_controller;
	static ControllerLinha		*_window_linha_controller;
	static ControllerPonto		*_window_ponto_controller;
	static ControllerPoligono	*_window_poligono_controller;

	static bool _initialized;
	static Controller *_instance;
};

#endif//__CONTROLLER_H__