#include "view/MainWindow.h"

MainWindow::MainWindow(GtkWidget * window) :
	Window(window)
{
	_drawing_area = GTK_DRAWING_AREA(find_child(_window, "mainwindow_drawing_area"));
	_tree_view = GTK_TREE_VIEW(find_child(_window, "treeview_main_object_list"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::initialize()
{
}

void MainWindow::onNotify(Events event)
{
}
