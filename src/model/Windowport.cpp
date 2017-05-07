#include "Windowport.h"

Windowport::Windowport(Vector position, Vector size, Viewport *viewport) :
	_transformation(),
	_size((size / 2.f) - 10),
	_vrp(0.f, 0.f, 0.f),
	_vpn(0.f, 0.f, 1.f)
{
	_center = Vector(position + (size / 2.f));

	_initial_position = _center - _size;
	_final_position = _center + _size;
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
	_transformation.translate(offset);
	_transformation.transformPoint(_vrp);
	_transformation.transformPoint(_vpn);

	notify(this, Events::WINDOW_MOVE);
}

void Windowport::rotate(Vector angles)
{

	_transformation.rotate(angles);
	_transformation.transformPoint(_vrp);
	_transformation.transformPoint(_vpn);


	notify(this, Events::WINDOW_ROTATE);


}

void Windowport::zoom(float factor)
{
	_transformation.scale(Vector(factor, factor, factor));
	_transformation.transformPoint(_vrp);

	notify(this, Events::WINDOW_ZOOM);
}

Transformation Windowport::getTransformation()
{
  return _transformation;
}

Vector *Windowport::normalize(Vector *vector)
{
	return new Vector((*_transformation.transformPoint(*vector) - _center) / _size);
}

float Windowport::unormalize_x(Vector *vector)
{
	return vector->x *_size.x;
}

float Windowport::unormalize_y(Vector *vector)
{
	return vector->y *_size.y;
}

Vector Windowport::unormalize(Vector *vector)
{
	return Vector(vector->x * _size.x, vector->y * _size.y, vector->z * _size.z);
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

	cairo_set_source_rgb(cr, 0, 0, 0);
}

Vector * Windowport::getInitWindowPosition()
{
	return &_initial_position;
}

Vector * Windowport::getFinalWindowPosition()
{
	return &_final_position;
}

Vector Windowport::getNormal()
{
	return _vpn;
}
