#ifndef __WINDOWPOLIGONO_H__
#define __WINDOWPOLIGONO_H__

#include "view/Window.h"
#include "util/Vector.h"
#include <vector>

class WindowPoligono : public Window
{
public:

	struct WinPoligono
	{
		const gchar *nome;
		std::vector<Vector> coords;
		WinPoligono(const gchar *nome, std::vector<Vector> coords) :
			nome(nome),
			coords(coords) {}

	};

	WindowPoligono(GtkWidget *window);
	void initialize();

	std::vector<Vector> add_coords();
	WinPoligono add_poligono(std::vector<Vector> v);

	virtual void onNotify(Events event);

private:
	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	std::vector<Vector> v;
	GtkTreeView* _treeView;
	GtkTreeIter    _iter;
	GtkTreeModel *_model;

};
#endif // !__WINDOWPOLIGONO_H__
