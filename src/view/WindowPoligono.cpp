#include "view/WindowPoligono.h"

WindowPoligono::WindowPoligono(GtkWidget * window) :
	Window(window)
{
	initialize();
	_entry_nome = GTK_ENTRY(find_child(window, "entry_poligono_nome"));
	assert(_entry_nome);

	_spinbutton_inicial_x = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_poligono_x"));
	assert(_spinbutton_inicial_x);

	_spinbutton_inicial_y = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_poligono_y"));
	assert(_spinbutton_inicial_y);

	_treeView = GTK_TREE_VIEW(find_child(_window, "treeview_poligono"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));

	_v = std::vector<Vector>();


}

void WindowPoligono::initialize()
{
}

Vector WindowPoligono::add_coords()
{
	gdouble inicial_x = gtk_spin_button_get_value(_spinbutton_inicial_x);
	gdouble inicial_y = gtk_spin_button_get_value(_spinbutton_inicial_y);
	g_print("x: %f, y: %f\n", inicial_x, inicial_y);

	//_v.push_back(Vector(inicial_x, inicial_y));
	gtk_list_store_append(GTK_LIST_STORE(_model), &_iter);
	gtk_list_store_set(GTK_LIST_STORE(_model),
												&_iter,
												0,
												inicial_x,
												1,
												inicial_y,
												-1);
	gtk_tree_view_set_model(GTK_TREE_VIEW(_treeView),
											 _model);
	return Vector(inicial_x, inicial_y);
}

WindowPoligono::WinPoligono WindowPoligono::add_poligono()
{
	const char* nome = gtk_entry_get_text(_entry_nome);
	gtk_widget_hide(_window);
	return WinPoligono(nome,_v);
}

void WindowPoligono::onNotify(Events event)
{
}
