#pragma once
#ifndef __CONTROLERMAINWINDOW_H__
#define __CONTROLERMAINWINDOW_H__

class Controller;
/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/Window.h"
#include "view/MainWindow.h"

#include "controller/Controller.h"

using namespace std;

class ControllerMainWindow
{
public:
	ControllerMainWindow(GtkBuilder *builder);

	~ControllerMainWindow();
	
	void display();
private:

	static void input_ponto_cb();
	static void input_poligono_cb();
	static void input_linha_cb();

	static MainWindow *_window;

	static Controller *_controller;

	

};

#endif//__CONTROLERMAINWINDOW_H__