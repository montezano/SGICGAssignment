#include "view/WindowLinha.h"

WindowLinha::WindowLinha(GtkWidget * window) :
	Window(window)
{
	initialize();
	_entry_nome = GTK_ENTRY(find_child(window, "entry_linha_nome"));
	assert(_entry_nome);

	_spinbutton_inicial_x = GTK_SPIN_BUTTON(find_child(window, "spinbutton_inicial_x"));
	assert(_spinbutton_inicial_x);

	_spinbutton_inicial_y = GTK_SPIN_BUTTON(find_child(window, "spinbutton_inicial_y"));
	assert(_spinbutton_inicial_y);

	_spinbutton_final_x = GTK_SPIN_BUTTON(find_child(window, "spinbutton_final_x"));
	assert(_spinbutton_final_x);

	_spinbutton_final_y = GTK_SPIN_BUTTON(find_child(window, "spinbutton_final_y"));
	assert(_spinbutton_final_y);
}

void WindowLinha::initialize()
{
}

WindowLinha::WinLinha WindowLinha::add_linha()
{
	
	const char* nome = gtk_entry_get_text(_entry_nome);
	gdouble inicial_x = gtk_spin_button_get_value(_spinbutton_inicial_x);
	gdouble inicial_y = gtk_spin_button_get_value(_spinbutton_inicial_y);
	gdouble final_x = gtk_spin_button_get_value(_spinbutton_final_x);
	gdouble final_y = gtk_spin_button_get_value(_spinbutton_final_y);
	gtk_widget_hide(_window);
	return WinLinha(nome, Vector(inicial_x, inicial_y), Vector(final_x, final_y));
}

void WindowLinha::onNotify(Events event)
{

}
