#include "controller/Controller.h"

Controller::Controller(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	_builder = gtk_builder_new();
	gtk_builder_add_from_file(_builder, MAIN_WINDOW_FILE, NULL);
	assert(_builder); ///< assert if the window was successfully created

	_main_window_controller = new ControllerMainWindow(_builder);
	_window_linha_controller = new ControllerLinha(_builder);
	_window_ponto_controller = new ControllerPonto(_builder);
		
	_window_poligono_controller = new ControllerPoligono(_builder);

	gtk_builder_connect_signals(_builder, NULL);
	g_print("Controller build sucessufuly\n");
}

Controller::~Controller()
{
}

Controller * Controller::getInstance()
{
	return _instance;
}

Controller * Controller::initialize(int argc, char * argv[])
{
	if (_initialized)
	{
		return _instance;
	}
	return new Controller(argc, argv);
}

void Controller::start()
{
	g_print("start\n");
	_main_window_controller->display();
	gtk_main();
	g_print("end\n");
}

ControllerMainWindow *Controller::_main_window_controller = NULL;
ControllerLinha		*Controller::_window_linha_controller = NULL;
ControllerPonto		*Controller::_window_ponto_controller = NULL;
ControllerPoligono	*Controller::_window_poligono_controller = NULL;

bool Controller::_initialized;
Controller *Controller::_instance;