#ifndef __WINDOWPORT_H__
#define __WINDOWPORT_H__

#include "Vector.h"
#include "Viewport.h"
#include "Transformation.h"

class Windowport
{
public:
  Windowport(Vector min, Vector max, Viewport *viewport);

  void setCenter(Vector position);
  void move(Vector offset);
  void rotate(float angle);
  void zoom(float factor);
  Transformation getTransformation();

private:
  Vector _position;
  Vector _size;
  float _angle;
  Viewport *_viewport;
  Transformation _transformation;
};

#endif //__WINDOWPORT_H__
