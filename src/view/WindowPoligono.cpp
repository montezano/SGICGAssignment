#include "WindowPoligono.h"

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

	_spinbutton_inicial_z = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_poligono_z"));
	assert(_spinbutton_inicial_z);

	_treeView = GTK_TREE_VIEW(find_child(_window, "treeview_poligono"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));

	_v = std::vector<Vector>();


}

void WindowPoligono::initialize()
{
}

Vector *WindowPoligono::add_coords()
{
	gfloat inicial_x = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_x));
	gfloat inicial_y = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_y));
	gfloat inicial_z = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_z));

	//_v.push_back(Vector(inicial_x, inicial_y));
	gtk_list_store_append(GTK_LIST_STORE(_model), &_iter);
	gtk_list_store_set(GTK_LIST_STORE(_model),
												&_iter,
												0,
												inicial_x,
												1,
												inicial_y,
												2,
												inicial_z,
												-1);
	gtk_tree_view_set_model(GTK_TREE_VIEW(_treeView),
											 _model);
	return new Vector(inicial_x, inicial_y, inicial_z);
}

WindowPoligono::WinPoligono WindowPoligono::add_poligono()
{
	const char* nome = gtk_entry_get_text(_entry_nome);
	gtk_widget_hide(_window);
	WinPoligono pol = WinPoligono(nome,_v);
	gtk_entry_set_text(_entry_nome,"" );
	gtk_spin_button_set_value (_spinbutton_inicial_x, 0.0);
	gtk_spin_button_set_value (_spinbutton_inicial_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_inicial_z, 0.0);

	gtk_list_store_clear(GTK_LIST_STORE(_model));
	return pol;
}

void WindowPoligono::onNotify(void *data, Events event)
{
}