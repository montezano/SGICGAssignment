#include <gtk/gtk.h>

#include <assert.h>
#include "Controller.h"

int main(int argc, char *argv[])
{

	Controller *cont = Controller::initialize(argc, argv);
	assert(cont);
	cont->start();
	return 0;
}
