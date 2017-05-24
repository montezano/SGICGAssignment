#include "WindowSurface.h"

WindowSurface::WindowSurface(GtkWidget * window, bool *bspline_curve) :
	Window(window)
{
	g_print("teste\n");
	initialize();
	_entry_nome = GTK_ENTRY(find_child(window, "entry_surface_nome"));
	assert(_entry_nome);

	_spinbutton_inicial_x = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_surface_x"));
	assert(_spinbutton_inicial_x);

	_spinbutton_inicial_y = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_surface_y"));
	assert(_spinbutton_inicial_y);

	_spinbutton_inicial_z = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_surface_z"));
	assert(_spinbutton_inicial_z);

	_treeView = GTK_TREE_VIEW(find_child(_window, "treeview_surface"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));
	_cont_label = GTK_LABEL(find_child(_window, "label_contador"));
	_cont = 16;
	_ok = GTK_BUTTON(find_child(_window, "button_ok_surface"));
	gtk_widget_set_sensitive(GTK_WIDGET(_ok), FALSE);

	_v = std::vector<Vector>();

	assert(bspline_curve);
	_bspline_curve = bspline_curve;


}

void WindowSurface::initialize()
{
}

Vector *WindowSurface::add_coords()
{	
	if (_cont != 0)
		_cont--;
	g_print("%d",_cont);
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
	gtk_label_set_text(_cont_label, std::to_string(_cont).c_str());

	if(_cont == 0){
		gtk_widget_set_sensitive(GTK_WIDGET(_ok), TRUE);
	}

	
	return new Vector(inicial_x, inicial_y, inicial_z);
}

WindowSurface::WinSurface WindowSurface::add_surface()
{	
	gtk_widget_set_sensitive(GTK_WIDGET(_ok), FALSE);
	_cont = 0;
	gtk_label_set_text(_cont_label, std::to_string(_cont).c_str());
	const char* nome = gtk_entry_get_text(_entry_nome);
	gtk_widget_hide(_window);
	WinSurface pol = WinSurface(nome,_v);
	gtk_entry_set_text(_entry_nome,"" );
	gtk_spin_button_set_value (_spinbutton_inicial_x, 0.0);
	gtk_spin_button_set_value (_spinbutton_inicial_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_inicial_z, 0.0);

	gtk_list_store_clear(GTK_LIST_STORE(_model));
	return pol;
}

void WindowSurface::onNotify(void *data, Events event)
{
}