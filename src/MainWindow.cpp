#include "MainWindow.h"
void MainWindow::initialize(int argc, char *argv[])
{
		gtk_init(&argc, &argv);

		_builder = gtk_builder_new();
		gtk_builder_add_from_file (_builder, MAIN_WINDOW_FILE, NULL);
    assert(_builder);	///< assert if the window was successfully created

    _main_window = GTK_WIDGET(gtk_builder_get_object(_builder, "main_window"));
		assert(_main_window); 	///< assert that the object main_window was found

    gtk_window_set_position(GTK_WINDOW(_main_window), GTK_WIN_POS_CENTER_ALWAYS);

		_window_box_input = GTK_WIDGET(gtk_builder_get_object(_builder, "window_linha"));
		assert(_window_box_input);

		gtk_window_set_position(GTK_WINDOW(_window_box_input), GTK_WIN_POS_CENTER_ALWAYS);

    gtk_builder_connect_signals(_builder, NULL);

    // _box_input = GTK_WIDGET(gtk_builder_get_object(_builder, "window1"));
    // assert(_box_input);

		GtkButton* button;

    button = GTK_BUTTON(gtk_builder_get_object(_builder,"button_linha"));
    assert(button);
		g_signal_connect (button, "clicked", G_CALLBACK (input_box), NULL);

    button = GTK_BUTTON(gtk_builder_get_object(_builder,"button_ponto"));
    assert(button);
		g_signal_connect (button, "clicked", G_CALLBACK (input_box), NULL);

    button = GTK_BUTTON(gtk_builder_get_object(_builder,"button_poligono"));
    assert(button);
		g_signal_connect (button, "clicked", G_CALLBACK (input_box), NULL);

		button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_cancel_linha"));
		assert(button);
		g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input);

		/// free _builder since it's no longer needed
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
void MainWindow::input_box()
{
	gtk_widget_show(_window_box_input);
}


// called when window is closed
void MainWindow::on_main_window_destroy()
{
    gtk_main_quit();
}



GtkBuilder* MainWindow::_builder;
GtkWidget* MainWindow::_main_window;
GtkWidget* MainWindow::_window_box_input;
