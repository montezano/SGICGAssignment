#include "Object3D.h"

Object3D::Object3D(const gchar *nome, std::vector<Line*> object, Windowport *window) :
  Polygon(nome, window),
  _object(object)
{
    _tipo = "objeto3d";
    updateWindow();
}

Object3D::~Object3D()
{

}

Object3D::getCenter()
{
  	Vector sum = Vector(0, 0, 0);
  	for (auto line : _object)
  	{
  		sum += *line.getCenter();
  	}

  	return sum / static_cast<float>(_object.size());
}
void Object3D::transform(Transformation &transformation)
{
    for(Line *line : _object)
    {
        line->transform(transformation);
    }
    updateWindow();
}

void Polygon::updateWindow()
{
    for (size_t i = 0; i < _object.size(); i++)
    {
  	     _coords_window[i] = _window->normalize(_coords[i]);
    }
    clip();
}
