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

WindowLinha::Linha WindowLinha::add_linha()
{
	
	WindowLinha::Linha linha;
	linha.nome = gtk_entry_get_text(_entry_nome);
	linha.tipo = "linha";
	linha.inicial_x = gtk_spin_button_get_value(_spinbutton_inicial_x);
	linha.inicial_y = gtk_spin_button_get_value(_spinbutton_inicial_y);
	linha.final_x = gtk_spin_button_get_value(_spinbutton_final_x);
	linha.final_y = gtk_spin_button_get_value(_spinbutton_final_y);

	gtk_widget_hide(_window);
	return linha;
}

void WindowLinha::onNotify(Events event)
{

}
