#ifndef SRC_MODEL_POINT_H_
#define SRC_MODEL_POINT_H_

#include "Drawable.h"
#include "Command.h"
#include <gtk/gtk.h>

class Point : public Drawable {

public:
	Point(const gchar *nome, gdouble inicial_x, gdouble inicial_, Windowport *windowy, Command *clipping);
	Point(const gchar *nome, Vector init_position, Windowport *window, Command *clipping);
	virtual ~Point();
	virtual void draw(cairo_t *_cr, Viewport *viewport);
	virtual Vector getCenter();
	virtual void transform(Transformation &transformation);
	virtual void updateWindow();
	void setVisible(bool state);
private:
	bool _visible;
	Command *_clipping;
};

#endif /* SRC_MODEL_POINT_H_ */
