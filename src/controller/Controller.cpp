#include "controller/Controller.h"

Controller::Controller(int argc, char *argv[])
{


	g_print("Controller build sucessufuly\n");
}

Controller::~Controller()
{
}

Controller * Controller::getInstance()
{
	assert(_instance);
	return _instance;
}

Controller * Controller::initialize(int argc, char * argv[])
{
	if (_initialized)
	{
		return _instance;
	}
	_instance = new Controller(argc, argv);
	assert(_instance);
	gtk_init(&argc, &argv);

	_builder = gtk_builder_new();
	gtk_builder_add_from_file(_builder, MAIN_WINDOW_FILE, NULL);

	_main_window_controller = new ControllerMainWindow(_builder);
	assert(_main_window_controller);
	_window_linha_controller = new ControllerLinha(_builder);
	assert(_window_linha_controller);
	_window_ponto_controller = new ControllerPonto(_builder);
	_window_poligono_controller = new ControllerPoligono(_builder);

	assert(_builder); ///< assert if the window was successfully created

	gtk_builder_connect_signals(_builder, NULL);
	return _instance;
}

void Controller::start()
{
	g_print("initialized\n");
	assert(_main_window_controller);
	_main_window_controller->display();
	g_print("start\n");
	gtk_main();
	g_print("end\n");
}

GtkBuilder *Controller::_builder = NULL;
ControllerMainWindow *Controller::_main_window_controller = NULL;
ControllerLinha		*Controller::_window_linha_controller = NULL;
ControllerPonto		*Controller::_window_ponto_controller = NULL;
ControllerPoligono	*Controller::_window_poligono_controller = NULL;

bool Controller::_initialized = false;
Controller *Controller::_instance = NULL;
