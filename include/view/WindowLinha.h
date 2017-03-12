#ifndef __WINDOWLINHA_H__
#define __WINDOWLINHA_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/Window.h"
#include "util/Vector.h"

class WindowLinha : public Window
{
public:


	WindowLinha(GtkWidget *window);
	void initialize();

	struct Line
	{
		const gchar *nome;
		Vector v_inicial;
		Vector v_final;
		Line(const gchar *nome, Vector inicial, Vector final) :
			nome(nome),
			v_inicial(inicial),
			v_final(final) {}
		
	};
	Line add_linha();

	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_final_x;
	GtkSpinButton *_spinbutton_final_y;

};


#endif //__WINDOWLINHA_H__
