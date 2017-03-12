#include "view/MainWindow.h"

MainWindow::MainWindow(GtkWidget * window) :
	Window(window)
{
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
