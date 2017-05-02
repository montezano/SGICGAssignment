#ifndef __OBJECT3D_H__
#define __OBJECT3D_H__

#include <gtk/gtk.h>

#include "Polygon.h"
#include "Line.h"

class Object3D : public Polygon
{

  public:
    Object3D(const gchar *nome, std::vector<Line*> object, Windowport *window);
    virtual ~Object3D();
    virtual void draw(cairo_t *_cr, Viewport *viewport);
    virtual Vector getCenter();
    virtual void transform(Transformation &transformation);
    virtual void updateWindow();
  private:
    std::vector<Line*> _object; //each pair represent a line
};

#endif /* __OBJECT3D_H__ */
