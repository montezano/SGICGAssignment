#include "MainWindow.h"
void MainWindow::initialize(int argc, char *argv[])
{
		gtk_init(&argc, &argv);

//    _builder = gtk_builder_new();
//    gtk_builder_add_from_file (_builder, MAIN_WINDOW_FILE, NULL);
    _builder = gtk_builder_new_from_file(MAIN_WINDOW_FILE);
    assert(_builder);	///< assert if the window was successfully created

    _main_window = GTK_WIDGET(gtk_builder_get_object(_builder, "main_window"));
    gtk_window_set_position(GTK_WINDOW(_main_window), GTK_WIN_POS_CENTER_ALWAYS);

    gtk_builder_connect_signals(_builder, NULL);
    assert(_main_window); 	///< assert that the object main_window was found

    // _box_input = GTK_WIDGET(gtk_builder_get_object(_builder, "window1"));
    // assert(_box_input);

    _button_line = GTK_BUTTON(gtk_builder_get_object(_builder,"button_linha"));
    assert(_button_line);

    _button_point = GTK_BUTTON(gtk_builder_get_object(_builder,"button_ponto"));
    assert(_button_point);

    _button_polygon = GTK_BUTTON(gtk_builder_get_object(_builder,"button_poligono"));
    assert(_button_polygon);


    g_signal_connect (_button_line, "clicked", G_CALLBACK (input_box), NULL);
    g_signal_connect (_button_point, "clicked", G_CALLBACK (input_box), NULL);
    g_signal_connect (_button_polygon, "clicked", G_CALLBACK (input_box), NULL);


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
  g_print ("Hello World\n");
  GtkWidget* box_input;
  GtkBuilder* b;
  b = gtk_builder_new();
  gtk_builder_add_from_file(b, MAIN_WINDOW_FILE, NULL);
  box_input = GTK_WIDGET(gtk_builder_get_object(b, "window1"));
  gtk_window_set_position(GTK_WINDOW(box_input), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_widget_show(box_input);
}


// called when window is closed
void MainWindow::on_main_window_destroy()
{
    gtk_main_quit();
}

GtkBuilder* MainWindow::_builder;
GtkWidget* MainWindow::_main_window;
GtkButton* MainWindow::_button_line;
GtkButton* MainWindow::_button_point;
GtkButton* MainWindow::_button_polygon;

