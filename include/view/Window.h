#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "util/Observer.h"
#include "util/Event.h"


#include <gtk/gtk.h>
#include "Viewport.h"
#include <assert.h>
#include <string>
#include <cstring>



class Window : public Observer
{
public:
	Window(GtkWidget *window);
	virtual ~Window();
	virtual void initialize() = 0;

	virtual void display();
	virtual void setWindow(GtkWidget *window);

	GtkWidget *getWindow();

	virtual void onNotify(void *data, Events event) = 0;

protected:

	GtkWidget *find_child(GtkWidget* parent, const gchar* name);
	GtkWidget *_window;
};
#endif // !__WINDOW_H__
