#ifndef __WINDOWLINHA_H__
#define __WINDOWLINHA_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>
#include <assert.h>

#include "view/Window.h"
#include "util/Vector.h"
#include "util/Event.h"

class WindowLinha : public Window
{
public:


	WindowLinha(GtkWidget *window);
	void initialize();

	struct WinLinha
	{
		std::string nome;
		Vector v_inicial;
		Vector v_final;
		WinLinha(const gchar *nome, Vector inicial, Vector final) :
			nome(nome),
			v_inicial(inicial),
			v_final(final) {}

	};
	WinLinha add_linha();

	virtual void onNotify(Drawable *data, Events event);


private:

	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_final_x;
	GtkSpinButton *_spinbutton_final_y;

};


#endif //__WINDOWLINHA_H__
