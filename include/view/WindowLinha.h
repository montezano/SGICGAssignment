#ifndef __WINDOWLINHA_H__
#define __WINDOWLINHA_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "Window.h"
#include "Vector.h"
#include "Event.h"

class WindowLinha : public Window
{
public:


	WindowLinha(GtkWidget *window);
	void initialize();

	struct WinLinha
	{
		std::string nome;
		Vector *v_inicial;
		Vector *v_final;
		WinLinha(const gchar *nome, Vector *inicial, Vector *final) :
			nome(nome),
			v_inicial(inicial),
			v_final(final) {}

	};
	WinLinha add_linha();

	virtual void onNotify(void *data, Events event);


private:

	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_inicial_z;

	GtkSpinButton *_spinbutton_final_x;
	GtkSpinButton *_spinbutton_final_y;
	GtkSpinButton *_spinbutton_final_z;


};


#endif //__WINDOWLINHA_H__
