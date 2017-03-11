#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <gtk/gtk.h>
#include <assert.h>
#include <string.h>

class Window
{
public:
	Window(GtkWidget *window);
	virtual ~Window();	
	virtual void initialize() = 0;

	virtual void display();


	virtual void setWindow(GtkWidget *window);
	GtkWidget *getWindow();
protected:

	GtkWidget *find_child(GtkWidget* parent, const gchar* name);
	GtkWidget *_window;
};
#endif // !__WINDOW_H__
