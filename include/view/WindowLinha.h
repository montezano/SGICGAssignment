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
		gchar *nome;
		gchar *tipo;
		gint x;
		gint y;
	};

	WindowLinha(GtkWidget *window);
	void initialize();

	Linha add_linha();

};


#endif //__WINDOWLINHA_H__