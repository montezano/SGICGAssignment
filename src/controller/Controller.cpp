#include "Controller.h"

Controller::Controller(int argc, char *argv[])
{
	gtk_init(&argc, &argv);


	_canvas = Canvas(&_viewport);

	_builder = gtk_builder_new();

	gtk_builder_add_from_file(_builder, MAIN_WINDOW_FILE, NULL);
	assert(_builder); ///< assert if the window was successfully created

	_main_window_controller = new ControllerMainWindow(_builder, this, &_canvas, &_viewport);
	assert(_main_window_controller);
	_window_linha_controller = new ControllerLinha(_builder, &_canvas);
	assert(_window_linha_controller);
	_window_ponto_controller = new ControllerPonto(_builder, &_canvas);
	assert(_window_ponto_controller);
	_window_poligono_controller = new ControllerPoligono(_builder, &_canvas);
	assert(_window_poligono_controller);


	gtk_builder_connect_signals(_builder, NULL);

	configureObservers();
}

void Controller::configureObservers()
{
	_canvas.addObserver(&_log);
	_canvas.addObserver(_main_window_controller->getWindow());

	_viewport.addObserver(&_log);
	_viewport.addObserver(_main_window_controller->getWindow());
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
	_instance = new Controller(argc, argv);
	assert(_instance);
	
	return _instance;
}

void Controller::start()
{
	assert(_main_window_controller);
	_main_window_controller->initialize();
	_main_window_controller->display();
	gtk_main();
}

void Controller::onNotify(void * data, Events event)
{
}

GtkBuilder *Controller::_builder = NULL;
ControllerMainWindow *Controller::_main_window_controller = NULL;
ControllerLinha		*Controller::_window_linha_controller = NULL;
ControllerPonto		*Controller::_window_ponto_controller = NULL;
ControllerPoligono	*Controller::_window_poligono_controller = NULL;

bool Controller::_initialized = false;
Controller *Controller::_instance = NULL;
Viewport Controller::_viewport;
Log Controller::_log;
Canvas Controller::_canvas;


