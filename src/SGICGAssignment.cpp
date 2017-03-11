#include <gtk/gtk.h>
#include "controller/Controller.h"

int main(int argc, char *argv[])
{

	Controller *cont = Controller::initialize(argc, argv);
	g_print("construiu\n");
	cont->start();
	return 0;
}
