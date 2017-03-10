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

    _window_box_input_line = GTK_WIDGET(gtk_builder_get_object(_builder, "window_linha"));
    assert(_window_box_input_line);

    gtk_window_set_position(GTK_WINDOW(_window_box_input_line), GTK_WIN_POS_CENTER_ALWAYS);
    
    _window_box_input_point = GTK_WIDGET(gtk_builder_get_object(_builder, "window_ponto"));
    assert(_window_box_input_point);

    gtk_window_set_position(GTK_WINDOW(_window_box_input_point), GTK_WIN_POS_CENTER_ALWAYS);
    
    _window_box_input_polygon = GTK_WIDGET(gtk_builder_get_object(_builder, "window_poligono"));
    assert(_window_box_input_polygon);

    gtk_window_set_position(GTK_WINDOW(_window_box_input_polygon), GTK_WIN_POS_CENTER_ALWAYS);

    gtk_builder_connect_signals(_builder, NULL);

    GtkButton* button;

    //Botões para chamar telas de linha,ponto ou poligono
    button = GTK_BUTTON(gtk_builder_get_object(_builder,"button_linha"));
    assert(button);
    g_signal_connect (button, "clicked", G_CALLBACK (input_box_line), NULL);

    button = GTK_BUTTON(gtk_builder_get_object(_builder,"button_ponto"));
    assert(button);
    g_signal_connect (button, "clicked", G_CALLBACK (input_box_point), NULL);

    button = GTK_BUTTON(gtk_builder_get_object(_builder,"button_poligono"));
    assert(button);
    g_signal_connect (button, "clicked", G_CALLBACK (input_box_polygon), NULL);

    //Botões cancel das telas de add
    button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_cancel_linha"));
    assert(button);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input_line);
    button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_cancel_ponto"));
    assert(button);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input_point);
    button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_cancel_poligono"));
    assert(button);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input_polygon);

    //Botões de ok das telas de add
    button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_ok_linha"));
    assert(button);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input_line);
    button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_ok_ponto"));
    assert(button);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input_point);
    button = GTK_BUTTON(gtk_builder_get_object(_builder, "button_ok_poligono"));
    assert(button);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_hide), _window_box_input_polygon);

    //Connect para nao destruir a widget no close
    g_signal_connect (_window_box_input_line, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
    g_signal_connect (_window_box_input_polygon, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);
    g_signal_connect (_window_box_input_point, "delete-event", G_CALLBACK (gtk_widget_hide_on_delete), NULL);


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
void MainWindow::input_box_line()
{
	gtk_widget_show(_window_box_input_line);
}
void MainWindow::input_box_point()
{
    gtk_widget_show(_window_box_input_point);
}
void MainWindow::input_box_polygon()
{
    gtk_widget_show(_window_box_input_polygon);
}

// called when window is closed
void MainWindow::on_main_window_destroy()
{
    gtk_main_quit();
}



GtkBuilder* MainWindow::_builder;
GtkWidget* MainWindow::_main_window;
GtkWidget* MainWindow::_window_box_input_point;
GtkWidget* MainWindow::_window_box_input_line;
GtkWidget* MainWindow::_window_box_input_polygon;