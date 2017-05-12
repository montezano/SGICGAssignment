#include "WindowObj3d.h"

WindowObj3d::WindowObj3d(GtkWidget * window) :
	Window(window)
{
	initialize();
	_entry_nome = GTK_ENTRY(find_child(window, "entry_obj3d_name"));
	assert(_entry_nome);

	_spinbutton_inicial_x = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_obj3d_x1"));
	assert(_spinbutton_inicial_x);

	_spinbutton_inicial_y = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_obj3d_y1"));
	assert(_spinbutton_inicial_y);

	_spinbutton_inicial_z = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_obj3d_z1"));
	assert(_spinbutton_inicial_z);

	_spinbutton_final_x = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_obj3d_x2"));
	assert(_spinbutton_inicial_x);

	_spinbutton_final_y = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_obj3d_y2"));
	assert(_spinbutton_inicial_y);

	_spinbutton_final_z = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_obj3d_z2"));
	assert(_spinbutton_inicial_z);

	_treeView = GTK_TREE_VIEW(find_child(_window, "treeview_obj3d"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));

	_v = std::vector<Vector>();


}

void WindowObj3d::initialize()
{
}

std::pair<Vector*, Vector*> WindowObj3d::add_edge()
{
	gfloat inicial_x = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_x));
	gfloat inicial_y = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_y));
	gfloat inicial_z = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_z));
	gfloat final_x = static_cast<float>(gtk_spin_button_get_value(_spinbutton_final_x));
	gfloat final_y = static_cast<float>(gtk_spin_button_get_value(_spinbutton_final_y));
	gfloat final_z = static_cast<float>(gtk_spin_button_get_value(_spinbutton_final_z));

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
	return std::make_pair(new Vector(inicial_x, inicial_y, inicial_z), new Vector(final_x, final_y, final_z));
}

std::string WindowObj3d::add_object3d()
{
	std::string nome = gtk_entry_get_text(_entry_nome);
	gtk_widget_hide(_window);
	gtk_entry_set_text(_entry_nome, "");
	gtk_spin_button_set_value(_spinbutton_inicial_x, 0.0);
	gtk_spin_button_set_value(_spinbutton_inicial_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_inicial_z, 0.0);
	gtk_spin_button_set_value(_spinbutton_final_x, 0.0);
	gtk_spin_button_set_value(_spinbutton_final_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_final_z, 0.0);

	gtk_list_store_clear(GTK_LIST_STORE(_model));
	return nome;
}

void WindowObj3d::onNotify(void *data, Events event)
{
}