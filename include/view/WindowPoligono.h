#ifndef __WINDOWPOLIGONO_H__
#define __WINDOWPOLIGONO_H__

#include "Window.h"
#include "util/Vector.h"
#include <vector>

class WindowPoligono : public Window
{
public:

	struct WinPoligono
	{
		std::string nome;
		std::vector<Vector> coords;
		WinPoligono(const gchar *nome, std::vector<Vector> aux_coords) :
			nome(nome),
			coords(aux_coords) {}

	};

	WindowPoligono(GtkWidget *window);
	void initialize();

	Vector add_coords();
	WinPoligono add_poligono();

	virtual void onNotify(void *data, Events event);


private:
	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	std::vector<Vector> _v;
	GtkTreeView* _treeView;
	GtkTreeIter    _iter;
	GtkTreeModel *_model;

};
#endif // !__WINDOWPOLIGONO_H__
