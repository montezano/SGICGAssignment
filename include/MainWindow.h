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
	static void input_box_point();
	static void input_box_line();
	static void input_box_polygon();


private:
	void configure_main_window();
	void on_main_window_destroy();
	//void input_box();


    static GtkBuilder *_builder;
    static GtkWidget *_main_window;
	static GtkWidget *_window_box_input_point;
	static GtkWidget *_window_box_input_line;
	static GtkWidget *_window_box_input_polygon;



};


#endif //__MAINWINDOW_H__
