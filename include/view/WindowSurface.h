#ifndef __WINDOWSURFACE_H__
#define __WINDOWSURFACE_H__

#include "Window.h"
#include "Vector.h"
#include <vector>

class WindowSurface : public Window
{
public:

	struct WinSurface
	{
		std::string nome;
		std::vector<Vector> coords;
		WinSurface(const gchar *nome, std::vector<Vector> aux_coords) :
			nome(nome),
			coords(aux_coords) {}

	};

	WindowSurface(GtkWidget *window, bool *curve_type);
	void initialize();

	Vector *add_coords();
	WinSurface add_surface();

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
	bool *_bspline_curve;

};
#endif // !__WINDOWPOLIGONO_H__
