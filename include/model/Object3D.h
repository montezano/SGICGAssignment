#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include <gtk/gtk.h>

#include "Drawable.h"
#include "Line.h"

class Object3D : public Drawable
{

  public:
	Object3D(const gchar *nome, std::vector<Line*> object, Windowport *window);
	virtual ~Object3D();
	virtual void draw(cairo_t *cr, Viewport *viewport);
	virtual Vector getCenter();
	virtual void transform(Transformation &transformation);
	virtual void updateWindow();
	
  private:
	virtual void clip();

	std::vector<Line*> _object; //each pair represent a line
	std::vector<Line*> _coords_window;
	std::vector<Line*> _clipped_coords;
};

#endif /* __OBJECT3D_H__ */
