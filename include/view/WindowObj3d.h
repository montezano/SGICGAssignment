#ifndef __WINDOWOBJ3D_H__
#define __WINDOWOBJ3D_H__

#include "Window.h"
#include <vector>
#include <utility>

class WindowObj3d : public Window
{
public:

	WindowObj3d(GtkWidget *window);
	void initialize();

	std::pair<Vector*, Vector*> add_edge();
	std::string add_object3d();

	virtual void onNotify(void *data, Events event);


private:
	GtkEntry *_entry_nome;
	GtkSpinButton *_spinbutton_inicial_x;
	GtkSpinButton *_spinbutton_inicial_y;
	GtkSpinButton *_spinbutton_inicial_z;
	GtkSpinButton *_spinbutton_final_x;
	GtkSpinButton *_spinbutton_final_y;
	GtkSpinButton *_spinbutton_final_z;

	std::vector<Vector> _v;
	GtkTreeView* _treeView;
	GtkTreeIter    _iter;
	GtkTreeModel *_model;

};
#endif // !__WINDOWOBJ3D_H__
