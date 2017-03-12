#ifndef __WINDOWLINHA_H__
#define __WINDOWLINHA_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>

#include <assert.h>

#include "view/Window.h"

class WindowLinha : public Window
{
public:

	struct Linha
	{
		const gchar *nome;
		const gchar *tipo;
		gdouble inicial_x;
		gdouble inicial_y;
		gdouble final_x;
		gdouble final_y;
	};

	WindowLinha(GtkWidget *window);
	void initialize();

	Linha add_linha();

	virtual void onNotify(Events event);

private:
	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_final_x;
	GtkSpinButton *_spinbutton_final_y;

};


#endif //__WINDOWLINHA_H__