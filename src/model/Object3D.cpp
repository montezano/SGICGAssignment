#include "Object3D.h"

Object3D::Object3D(const gchar *nome, std::vector<Line*> object, Windowport *window) :
  Drawable(nome, window),
  _object(object)
{
	_tipo = "objeto3d";
        g_print("size -------------%d",_object.size());
	updateWindow();
}

Object3D::~Object3D()
{

}

void Object3D::draw(cairo_t * cr, Viewport * viewport)
{
	for (auto line : _object)
	{
		line->draw(cr, viewport);
	}
}

Vector Object3D::getCenter()
{
	Vector sum = Vector(0, 0, 0);
	for (auto line : _object)
	{
		sum += line->getCenter();
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

void Object3D::updateWindow()
{
	for (auto line : _object)
	{
		 line->updateWindow();
	}
}

void Object3D::clip()
{
}
