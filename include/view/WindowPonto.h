#ifndef __WINDOWPONTO_H__
#define __WINDOWPONTO_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>

#include <assert.h>

#include "view/Window.h"
#include "util/Vector.h"

class WindowPonto : public Window
{
public:

	struct WinPonto
	{
		std::string nome;
		Vector v_inicial;
		WinPonto(const gchar *nome, Vector inicial) :
			nome(nome),
			v_inicial(inicial) {}

	};

	WindowPonto(GtkWidget *window);
	void initialize();

	WinPonto add_ponto();

	virtual void onNotify(Drawable *data, Events event);

private:
	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;

};


#endif //__WINDOWPONTO_H__
