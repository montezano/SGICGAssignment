#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

/////////////////////////////////
/// CONFIGURATIONS
/////////////////////////////////
#define MAIN_WINDOW_FILE "./ui/main_window.glade"

/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>

#include <assert.h>

class MainWindow
{
public:
	static void initialize(int argc, char *argv[]);
	static void display();

private:
	void configure_main_window();
	void on_main_window_destroy();

    static GtkBuilder      *_builder;
    static GtkWidget       *_main_window;
};


#endif //__MAINWINDOW_H__
