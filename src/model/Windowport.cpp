#include "Windowport.h"

Windowport::Windowport(Vector min, Vector max, Viewport *viewport) :
  _transformation()
{
  _position = Vector(max.x - (min.x/2), max.y - (min.y/2));
  _size = Vector((max.x - min.x)/2, (max.y - min.y)/2);
  _angle = 0.f;
}

void Windowport::setCenter(Vector position)
{
  _position = position;
}

void Windowport::move(Vector offset)
{
  setCenter(_position + offset);
}

void Windowport::rotate(float angle)
{
  _transformation.rotate(angle);
}

void Windowport::zoom(float factor)
{
  _size.x = _size.x * factor;
  _size.y = _size.y * factor;
}

Transformation Windowport::getTransformation()
{
  return _transformation;
}
