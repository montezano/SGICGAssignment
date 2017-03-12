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

	virtual void onNotify(Events event);

private:
	GtkTreeView* _tree_view;
	GtkDrawingArea* _drawing_area;


};


#endif //__MAINWINDOW_H__
