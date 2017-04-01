#include "Controller.h"

Controller::Controller(int argc, char *argv[]) :
	_windowport(Vector(-300, -300), Vector(600, 600), &_viewport)
{
	gtk_init(&argc, &argv);

	_point_clipping = new PointClipping();
	_line_clipping = new CSClipping();

	_canvas = Canvas(&_viewport, &_windowport, _point_clipping, _line_clipping, _polygon_clipping);

	_builder = gtk_builder_new();

	gtk_builder_add_from_file(_builder, MAIN_WINDOW_FILE, NULL);
	assert(_builder); ///< assert if the window was successfully created

	_main_window_controller = new ControllerMainWindow(_builder, this, &_canvas, &_viewport, &_windowport);
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

	_windowport.addObserver(&_log);
	_windowport.addObserver(_main_window_controller->getWindow());
	_windowport.addObserver(&_canvas);

	_main_window_controller->getWindow()->addObserver(this);
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

	switch (event)
	{
	case MAINWINDOW_RECONFIGURE:
		Vector size = *static_cast<Vector*>(data);
		_viewport.setSize(size);
		_windowport.setSize(size);
		_canvas.updateWindow();
		break;
	}
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

Command *Controller::_point_clipping = NULL;
Command *Controller::_line_clipping = NULL;
Command *Controller::_polygon_clipping = NULL;



