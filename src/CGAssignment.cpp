#include <gtk/gtk.h>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
	MainWindow::initialize(argc, argv);
	MainWindow::display();

    return 0;
}

// called when window is closed
void on_main_window_destroy()
{
    gtk_main_quit();
}
