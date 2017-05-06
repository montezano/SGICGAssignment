#ifndef __WINDOWBESIER_H__
#define __WINDOWBESIER_H__

#include "Window.h"
#include "Vector.h"
#include <vector>

class WindowBesier : public Window
{
public:

	struct WinBesier
	{
		std::string nome;
		std::vector<Vector> coords;
		WinBesier(const gchar *nome, std::vector<Vector> aux_coords) :
			nome(nome),
			coords(aux_coords) {}

	};

	WindowBesier(GtkWidget *window);
	void initialize();

	Vector *add_coords();
	WinBesier add_besier();

	virtual void onNotify(void *data, Events event);


private:
	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_inicial_z;

	GtkButton* _ok;
	std::vector<Vector> _v;
	GtkTreeView* _treeView;
	GtkTreeIter    _iter;
	int _cont;
	GtkLabel* _cont_label;
	GtkTreeModel *_model;

};
#endif // !__WINDOWPOLIGONO_H__
