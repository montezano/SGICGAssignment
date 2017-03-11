#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <gtk/gtk.h>
#include <assert.h>

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
	GtkWidget *_window;
};
#endif // !__WINDOW_H__
