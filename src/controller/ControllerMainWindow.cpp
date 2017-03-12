#include "controller/ControllerMainWindow.h"

ControllerMainWindow::ControllerMainWindow(GtkBuilder * builder)
{
	_window = new MainWindow(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")));

	_controller = Controller::getInstance();

	GtkButton* button;

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_ponto"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(input_ponto_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_linha"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(input_linha_cb), NULL);

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_poligono"));
	assert(button);
	g_signal_connect(button, "clicked", G_CALLBACK(input_poligono_cb), NULL);

	treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "object_list_treeview"));

//	GtkTreeIter    iter;
//	GtkTreeModel *model;
//	model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));
//	gtk_list_store_append(GTK_LIST_STORE(model), &iter);
//	gtk_list_store_set(GTK_LIST_STORE(model),
//	                      &iter,
//	                      0,
//	                      "John",
//	                      1,
//	                      "Doe",
//	                      2,
//	                      "Somewhere",
//	                      3,
//	                      "KS",
//	                      -1);
//	gtk_tree_view_set_model(GTK_TREE_VIEW(treeView),
//	                           model);

}

ControllerMainWindow::~ControllerMainWindow()
{
}

void ControllerMainWindow::display()
{
	_window->display();
}

void ControllerMainWindow::input_ponto_cb()
{
	g_print("ponto\n");
	_controller->_window_ponto_controller->display();
}

void ControllerMainWindow::input_poligono_cb()
{
	g_print("poligono\n");
	_controller->_window_poligono_controller->display();
}

//void ControllerMainWindow::addItemListView(WindowLinha::Linha linha)
//{
//
//
//}

void ControllerMainWindow::input_linha_cb()
{
	g_print("linha\n");
	_controller->_window_linha_controller->display();
}

MainWindow *ControllerMainWindow::_window;
Controller *ControllerMainWindow::_controller;
