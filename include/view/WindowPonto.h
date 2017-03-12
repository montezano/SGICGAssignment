#ifndef __WINDOWPONTO_H__
#define __WINDOWPONTO_H__



/////////////////////////////////
/// HEADERS
/////////////////////////////////
#include <gtk/gtk.h>

#include <assert.h>

#include "view/Window.h"

class WindowPonto : public Window
{
public:

	struct Ponto
	{
		gchar *nome;
		gchar *tipo;
		gint x;
		gint y;
	};

	WindowPonto(GtkWidget *window);	
	void initialize();

	Ponto add_ponto();

	virtual void onNotify(Events event);

};


#endif //__WINDOWPONTO_H__