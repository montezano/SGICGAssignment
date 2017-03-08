#include "MainWindow.h"

void MainWindow::initialize(int argc, char *argv[])
{
		gtk_init(&argc, &argv);

//    _builder = gtk_builder_new();
//    gtk_builder_add_from_file (_builder, MAIN_WINDOW_FILE, NULL);
    _builder = gtk_builder_new_from_file(MAIN_WINDOW_FILE);
    assert(_builder);	///< assert if the window was successfully created

    _main_window = GTK_WIDGET(gtk_builder_get_object(_builder, "main_window"));
    gtk_builder_connect_signals(_builder, NULL);
    assert(_main_window); 	///< assert that the object main_window was found
    g_object_unref(_builder);
}
void MainWindow::display()
{
    gtk_widget_show(_main_window);
    gtk_main();
}

void MainWindow::configure_main_window()
{

}

// called when window is closed
void MainWindow::on_main_window_destroy()
{
    gtk_main_quit();
}

GtkBuilder* MainWindow::_builder;
GtkWidget* MainWindow::_main_window;
