#include "Windowport.h"

Windowport::Windowport(Vector position, Vector size, Viewport *viewport) :
	_transformation(),
	_size((size / 2.f) - 10)
{
	_center = Vector(position + (size / 2.f));
	_angle = 0.f;
}

void Windowport::setSize(Vector vector)
{
	_size = (vector / 2.f) - 10;

}

void Windowport::setCenter(Vector position)
{
  _center = position;

  notify(this, Events::WINDOW_MOVE);
}

void Windowport::move(Vector offset)
{
  //setCenter(_center + offset);
	_transformation = _transformation.translate(offset);
	notify(this, Events::WINDOW_MOVE);
}

void Windowport::rotate(float angle)
{
  _transformation = _transformation.rotate(-angle);

  notify(this, Events::WINDOW_ROTATE);
}

void Windowport::zoom(float factor)
{
  /*_size.x = _size.x * factor;
  _size.y = _size.y * factor;*/

	_transformation = _transformation.scale(Vector(factor, factor));

	notify(this, Events::WINDOW_ZOOM);
}

Transformation Windowport::getTransformation()
{
  return _transformation;
}

Vector Windowport::normalize(Vector & vector)
{
	return (_transformation.transformPoint(vector) - _center) / _size;
}

float Windowport::unormalize_x(Vector & vector)
{
	return vector.x *_size.x;
}

float Windowport::unormalize_y(Vector & vector)
{
	return vector.y *_size.y;
}

void Windowport::draw(cairo_t *cr, Viewport *viewport)

{

	cairo_set_source_rgb(cr, 255, 0, 0);


	cairo_move_to(cr, viewport->transformX(_center.x - _size.x), viewport->transformY(_center.y - _size.y));
	cairo_line_to(cr, viewport->transformX(_center.x + _size.x), viewport->transformY(_center.y - _size.y));

	cairo_move_to(cr, viewport->transformX(_center.x + _size.x), viewport->transformY(_center.y - _size.y));
	cairo_line_to(cr, viewport->transformX(_center.x + _size.x), viewport->transformY(_center.y + _size.y));

	cairo_move_to(cr, viewport->transformX(_center.x + _size.x), viewport->transformY(_center.y + _size.y));
	cairo_line_to(cr, viewport->transformX(_center.x - _size.x), viewport->transformY(_center.y + _size.y));

	cairo_move_to(cr, viewport->transformX(_center.x - _size.x), viewport->transformY(_center.y + _size.y));
	cairo_line_to(cr, viewport->transformX(_center.x - _size.x), viewport->transformY(_center.y - _size.y));

	cairo_stroke(cr);
}