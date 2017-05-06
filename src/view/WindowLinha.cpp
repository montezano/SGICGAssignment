#include "WindowLinha.h"

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

	_spinbutton_inicial_z = GTK_SPIN_BUTTON(find_child(window, "spinbutton_inicial_z"));
	assert(_spinbutton_inicial_z);

	_spinbutton_final_x = GTK_SPIN_BUTTON(find_child(window, "spinbutton_final_x"));
	assert(_spinbutton_final_x);

	_spinbutton_final_y = GTK_SPIN_BUTTON(find_child(window, "spinbutton_final_y"));
	assert(_spinbutton_final_y);

	_spinbutton_final_z = GTK_SPIN_BUTTON(find_child(window, "spinbutton_final_z"));
	assert(_spinbutton_final_z);
}

void WindowLinha::initialize()
{
}

WindowLinha::WinLinha WindowLinha::add_linha()
{
	const char* nome = gtk_entry_get_text(_entry_nome);
	gfloat inicial_x = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_x));
	gfloat inicial_y = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_y));
	gfloat inicial_z = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_z));

	gfloat final_x = static_cast<float>(gtk_spin_button_get_value(_spinbutton_final_x));
	gfloat final_y = static_cast<float>(gtk_spin_button_get_value(_spinbutton_final_y));
	gfloat final_z = static_cast<float>(gtk_spin_button_get_value(_spinbutton_final_z));

	gtk_widget_hide(_window);
	WinLinha linha = WinLinha(nome, new Vector(inicial_x, inicial_y, inicial_z), new Vector(final_x, final_y, final_z));
	gtk_entry_set_text(_entry_nome,"" );
	gtk_spin_button_set_value (_spinbutton_inicial_x, 0.0);
	gtk_spin_button_set_value (_spinbutton_inicial_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_inicial_z, 0.0);

	gtk_spin_button_set_value (_spinbutton_final_x, 0.0);
	gtk_spin_button_set_value (_spinbutton_final_y, 0.0);
	gtk_spin_button_set_value(_spinbutton_final_z, 0.0);

	return linha;
}

void WindowLinha::onNotify(void *data, Events event)
{
}