#include "WindowBesier.h"

WindowBesier::WindowBesier(GtkWidget * window, bool *bspline_curve) :
	Window(window)
{
	g_print("teste\n");
	initialize();
	_entry_nome = GTK_ENTRY(find_child(window, "entry_besier_nome"));
	assert(_entry_nome);

	_spinbutton_inicial_x = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_besier_x"));
	assert(_spinbutton_inicial_x);

	_spinbutton_inicial_y = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_besier_y"));
	assert(_spinbutton_inicial_y);

	_spinbutton_inicial_z = GTK_SPIN_BUTTON(find_child(_window, "spinbutton_besier_z"));
	assert(_spinbutton_inicial_z);

	_treeView = GTK_TREE_VIEW(find_child(_window, "treeview_besier"));
	_model = gtk_tree_view_get_model(GTK_TREE_VIEW(_treeView));
	_cont_label = GTK_LABEL(find_child(_window, "label_contador"));
	_cont = 0;
	_ok = GTK_BUTTON(find_child(_window, "button_ok_besier"));
	gtk_widget_set_sensitive(GTK_WIDGET(_ok), FALSE);

	_v = std::vector<Vector>();

	assert(bspline_curve);
	_bspline_curve = bspline_curve;


}

void WindowBesier::initialize()
{
}

Vector *WindowBesier::add_coords()
{	
	_cont++;
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

	if (*_bspline_curve)
	{
		if (_cont > 3) {
			gtk_widget_set_sensitive(GTK_WIDGET(_ok), TRUE);
		}
		else
		{
			gtk_widget_set_sensitive(GTK_WIDGET(_ok), FALSE);
		}
	}
	else
	{
		if (_cont > 3 && !((_cont - 4) % 3)) {
			gtk_widget_set_sensitive(GTK_WIDGET(_ok), TRUE);
		}
		else
		{
			gtk_widget_set_sensitive(GTK_WIDGET(_ok), FALSE);
		}
	}

	
	return new Vector(inicial_x, inicial_y, inicial_z);
}

WindowBesier::WinBesier WindowBesier::add_besier()
{	
	gtk_widget_set_sensitive(GTK_WIDGET(_ok), FALSE);
	_cont = 4;
	gtk_label_set_text(_cont_label, std::to_string(_cont).c_str());
	const char* nome = gtk_entry_get_text(_entry_nome);
	gtk_widget_hide(_window);
	WinBesier pol = WinBesier(nome,_v);
	gtk_entry_set_text(_entry_nome,"" );
	gtk_spin_button_set_value (_spinbutton_inicial_x, 0.0);
	gtk_spin_button_set_value (_spinbutton_inicial_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_inicial_z, 0.0);

	gtk_list_store_clear(GTK_LIST_STORE(_model));
	return pol;
}

void WindowBesier::onNotify(void *data, Events event)
{
}