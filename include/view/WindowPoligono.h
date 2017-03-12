#ifndef __WINDOWPOLIGONO_H__
#define __WINDOWPOLIGONO_H__

#include "view/Window.h"

class WindowPoligono : public Window
{
public:

	struct Poligono
	{
		gchar *nome;
		gchar *tipo;
		gint x;
		gint y;
	};

	WindowPoligono(GtkWidget *window);
	void initialize();

	Poligono add_poligono();

	virtual void onNotify(Events event);

};
#endif // !__WINDOWPOLIGONO_H__
