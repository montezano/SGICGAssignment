#include "Line.h"
#include "Viewport.h"

#include <assert.h>

#define CS_MIDDLE		0
#define CS_TOP			1 << 1
#define CS_BOTTOM		1 << 2
#define CS_RIGHT		1 << 3
#define CS_LEFT			1 << 4
#define CS_TOP_LEFT		CS_TOP | CS_LEFT
#define CS_TOP_RIGHT	CS_TOP | CS_RIGHT
#define CS_BOTTOM_LEFT	CS_BOTTOM | CS_LEFT
#define CS_BOTTOM_RIGHT	CS_BOTTOM | CS_RIGHT

 Line::Line(const gchar * nome, float inicial_x, float inicial_y, float final_x, float final_y, Windowport *window) :
	 Drawable(nome, inicial_x, inicial_y, window),
	 _final_position(Vector(final_x, final_y)),
	 _final_position_window(Vector(final_x, final_y))
 {
	 updateWindow();
 }

 Line::Line(const gchar * nome, Vector init_position, Vector final_position, Windowport *window) :
	 Drawable(nome, init_position, window),
	 _final_position(final_position),
	 _final_position_window(final_position)
 {
	 updateWindow();
 }

Line::~Line()
{
}

void Line::draw(cairo_t *_cr, Viewport *viewport)
{
	if (_visible)
	{
		cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_position)), viewport->transformY(_window->unormalize_y(_clipped_position)));
		cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_final_position)), viewport->transformY(_window->unormalize_y(_clipped_final_position)));
	}
	cairo_stroke(_cr);
}

Vector Line::getCenter()
{
	return (_position + _final_position) / 2.f;
}

void Line::transform(Transformation & transformation)
{
	_position = transformation.transformPoint(_position);
	_final_position = transformation.transformPoint(_final_position);
	updateWindow();
}

void Line::updateWindow()
{
	_position_window = _window->normalize(_position);
	_final_position_window = _window->normalize(_final_position);
	clip();
}

Vector Line::getFinalPosition()
{
	return _final_position;
}

Vector Line::getFinalPositionWindow()
{
	return _final_position_window;
}

void Line::setClippingAlgorithm(LineAlgorithm alg)
{
	_line_alg = alg;
}

void Line::clip()
{
	switch (_line_alg)
	{
	case CS:
	 CSClip();
		break;
	case LB:
	LBClip();
	break;
  default:
	LBClip();
	break;
	}

}

void Line::LBClip()
{
	float p[4], q[4], r[4];
	float max, min;
	float dx, dy;
	_clipped_position = _position_window;
	_clipped_final_position = _final_position_window;

	dx = _final_position_window.x - _position_window.x;
	dy = _final_position_window.y - _position_window.y;

	p[0] = -dx;
	p[1] = dx;
	p[2] = -dy;
	p[3] = dy;

	q[0] = (_position_window.x - (-1));
	q[1] = (1 - _position_window.x);
	q[2] = (_position_window.y - (-1));
	q[3] = (1 - _position_window.y);

  for (int i = 0; i < 4; i++) {
	if (p[i] == 0) {
	  if (i & 0x02) { // dy == 0
		if ((_position_window.y > 1) || (_position_window.y < -1)) { // outside window
		  _visible = false;
		  return;
		}
		if (_position_window.x > 1) {
		  _clipped_position.x = 1;
		}
		else if (_position_window.x < -1) {
		  _clipped_position.x = -1;
		}
		if (_final_position_window.x > 1) {
		  _clipped_final_position.x = 1;
		}
		else if (_final_position_window.x < -1) {
		  _clipped_final_position.x = -1;
		}
		return;
	  } else { // dx == 0
		if ((_position_window.x > 1) || (_position_window.x < -1)) { // outside window
		  _visible = false;
		  return;
		}
		if (_position_window.y > 1) {
		  _clipped_position.y = 1;
		}
		else if (_position_window.y < -1) {
		  _clipped_position.y = -1;
		}
		if (_final_position_window.y > 1) {
		  _clipped_final_position.y = 1;
		}
		else if (_final_position_window.y < -1) {
		  _clipped_final_position.y = -1;
		}
		_visible = true;
		return;
	  }
	}
  }

  for (int i = 0; i < 4; i++)
	r[i] = q[i]/p[i];

  if ((p[0] <= 0) && (p[2] <= 0)){
	max = std::max({(float)0, r[0], r[2]});
	min = std::min({(float)1, r[1], r[3]});
  } else if ((p[1] <= 0) && (p[2] <= 0)) {
	max = std::max({(float)0, r[1], r[2]});
	min = std::min({(float)1, r[0], r[3]});
  } else if ((p[0] <= 0) && (p[3] <= 0)) {
	max = std::max({(float)0, r[0], r[3]});
	min = std::min({(float)1, r[1], r[2]});
  } else if ((p[1] <= 0) && (p[3] <= 0)) {
	max = std::max({(float)0, r[1], r[3]});
	min = std::min({(float)1, r[0], r[2]});
  }

  if (max > min){
	_visible = false;
   return;
 }

  if (min < 1) {
	_clipped_final_position.x = _position_window.x + (min*dx);
	_clipped_final_position.y = _position_window.y + (min*dy);

  }
  if (max > 0) {
	_clipped_position.x = _position_window.x + (max*dx);
	_clipped_position.y = _position_window.y + (max*dy);
  }
  _visible = true;
  return;
}

void Line::CSClip()
{
	Vector v_initial = _position_window;
	Vector v_final = _final_position_window;
	unsigned int region_initial = getCSRegion(v_initial);
	unsigned int region_final = getCSRegion(v_final);
	unsigned int region = region_initial | region_final;
	_visible = true;

	if (!region)
	{
		_clipped_position = v_initial;
		_clipped_final_position = v_final;
	}
	else
	{
		if (region_initial & region_final)
		{
			_visible = false;
		}
		else
		{
			float m = (v_initial.y - v_final.y) / (v_initial.x - v_final.x);
			if (region_initial)
			{
				v_initial = clipCSLine(region_initial, v_initial, m);
			}
			if (region_final)
			{
				v_final = clipCSLine(region_final, v_final, m);
			}
			_clipped_position = v_initial;
			_clipped_final_position = v_final;
		}
	}
}



unsigned int Line::getCSRegion(Vector &vector)
{
	unsigned int placement_x = 0;
	unsigned int placement_y = 0;
	if (vector.x < -1)
	{
		placement_x = CS_LEFT;
	}
	else
	{
		if (vector.x > 1)
		{
			placement_x = CS_RIGHT;
		}
	}

	if (vector.y < -1)
	{
		placement_y = CS_BOTTOM;
	}
	else
	{
		if (vector.y > 1)
		{
			placement_y = CS_TOP;
		}
	}

	return placement_x | placement_y;
}

Vector Line::clipCSLine(unsigned int &region, Vector &vector1, float coeficient)
{
	Vector ret = vector1;
	float x, y;
	switch (region)
	{
	case CS_TOP:
		x = vector1.x + 1.f / coeficient * (1.f - vector1.y);
		if (x < -1 || x > 1)
		{
			return ret;
		}
		ret.y = 1.f;

		ret.x = x;
		break;
	case CS_BOTTOM:
		x = vector1.x + 1.f / coeficient * (-1.f - vector1.y);
		if (x < -1 || x > 1)
		{
			return ret;
		}
		ret.y = -1.f;
		ret.x = x;
		break;
	case CS_RIGHT:
		y = coeficient*(1.f - vector1.x) + vector1.y;
		if (y < -1 || y > 1)
		{
			return ret;
		}
		ret.x = 1.f;

		ret.y = y;
		break;
	case CS_LEFT:
		y = coeficient*(-1.f - vector1.x) + vector1.y;
		if (y < -1 || y > 1)
		{
			return ret;
		}
		ret.x = -1.f;
		ret.y = y;
		break;
	case CS_TOP_LEFT:
		y = coeficient*(-1.f - vector1.x) + vector1.y;
		x = vector1.x + 1.f / coeficient * (1.f - vector1.y);
		if (y > -1 && y < 1)
		{
			ret.x = -1;
			ret.y = y;
		}
		else
		{
			if (x > -1 && x < 1)
			{
				ret.x = x;
				ret.y = 1;
			}
			else
			{
				_visible = false;
			}


		}
		break;
	case CS_TOP_RIGHT:
		y = coeficient*(1.f - vector1.x) + vector1.y;
		x = vector1.x + 1.f / coeficient * (1.f - vector1.y);
		if (y > -1 && y < 1)
		{
			ret.x = 1;
			ret.y = y;
		}
		else
		{
			if (x > -1 && x < 1)
			{
				ret.x = x;
				ret.y = 1;
			}
			else
			{
				_visible = false;
			}

		}
		break;
	case CS_BOTTOM_LEFT:
		y = coeficient*(-1.f - vector1.x) + vector1.y;
		x = vector1.x + 1.f / coeficient * (-1.f - vector1.y);
		if (y > -1 && y < 1)
		{
			ret.x = -1;
			ret.y = y;
		}
		else
		{
			if (x > -1 && x < 1)
			{
				ret.x = x;
				ret.y = -1;
			}
			else
			{
				_visible = false;
			}

		}
		break;
	case CS_BOTTOM_RIGHT:
		y = coeficient*(1.f - vector1.x) + vector1.y;
		x = vector1.x + 1.f / coeficient * (-1.f - vector1.y);
		if (y > -1 && y < 1)
		{
			ret.x = 1;
			ret.y = y;
		}
		else
		{
			if (x > -1 && x < 1)
			{
				ret.x = x;
				ret.y = -1;
			}
			else
			{
				_visible = false;
			}
		}
		break;
	}
	return ret;
}

Line::LineAlgorithm Line::_line_alg = Line::LineAlgorithm::CS;
