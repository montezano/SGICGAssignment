#include "WindowPonto.h"

WindowPonto::WindowPonto(GtkWidget * window) :
	Window(window)
{
	initialize();
	_entry_nome = GTK_ENTRY(find_child(window, "entry_nome"));
	assert(_entry_nome);

	_spinbutton_inicial_x = GTK_SPIN_BUTTON(find_child(window, "spin_button_ponto_x"));
	assert(_spinbutton_inicial_x);

	_spinbutton_inicial_y = GTK_SPIN_BUTTON(find_child(window, "spin_button_ponto_y"));
	assert(_spinbutton_inicial_y);
}

void WindowPonto::initialize()
{
}

WindowPonto::WinPonto WindowPonto::add_ponto()
{
	const char* nome = gtk_entry_get_text(_entry_nome);
	gfloat inicial_x = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_x));
	gfloat inicial_y = static_cast<float>(gtk_spin_button_get_value(_spinbutton_inicial_y));
	gtk_widget_hide(_window);
	WinPonto p = WinPonto(nome, Vector(inicial_x, inicial_y));
	gtk_entry_set_text(_entry_nome, "");
	gtk_spin_button_set_value (_spinbutton_inicial_x, 0.0);
	gtk_spin_button_set_value (_spinbutton_inicial_y, 0.0);
	return p;
}

void WindowPonto::onNotify(void *data, Events event)
{
}
