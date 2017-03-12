#ifndef __WINDOWLINHA_H__
#define __WINDOWLINHA_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include "model/Line.h"
#include <assert.h>

#include "view/Window.h"

class WindowLinha : public Window
{
public:


	WindowLinha(GtkWidget *window);
	void initialize();

	Line* add_linha();

	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_final_x;
	GtkSpinButton *_spinbutton_final_y;

};


#endif //__WINDOWLINHA_H__
