#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>

#include <assert.h>

#include "view/Window.h"

class MainWindow : public Window
{
public:

	MainWindow(GtkWidget *window);
	virtual ~MainWindow();
	void initialize();

};


#endif //__MAINWINDOW_H__
