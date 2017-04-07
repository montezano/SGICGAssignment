#include "Polygon.h"
#include "Viewport.h"

#include <assert.h>
#include <stdlib.h>

#define CS_MIDDLE		0
#define CS_TOP			1 << 1
#define CS_BOTTOM		1 << 2
#define CS_RIGHT		1 << 3
#define CS_LEFT			1 << 4
#define CS_TOP_LEFT		CS_TOP | CS_LEFT
#define CS_TOP_RIGHT	CS_TOP | CS_RIGHT
#define CS_BOTTOM_LEFT	CS_BOTTOM | CS_LEFT
#define CS_BOTTOM_RIGHT	CS_BOTTOM | CS_RIGHT



 Polygon::Polygon(const gchar * nome, double inicial_x, double inicial_y, std::vector<Vector> coords, Windowport *window) :
	 Drawable(nome, inicial_x, inicial_y, window),
	 _coords(coords),
	 _coords_window(coords)
 {
	 updateWindow();
 }

 Polygon::Polygon(const gchar * nome, Vector init_position, std::vector<Vector> coords, Windowport *window) :
	 Drawable(nome, init_position, window),
	 _coords(coords),
	 _coords_window(coords)
 {
	 updateWindow();
 }

Polygon::~Polygon()
{
	// TODO Auto-generated destructor stub
}

void Polygon::draw(cairo_t *_cr, Viewport *viewport)

{
	//assert(surface);
	//_cr = cairo_create(surface);
	//cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_position_window)), viewport->transformY(_window->unormalize_y(_position_window)));
	if (_clipped_coords.size() > 0)
	{
		for (size_t i = 0; i < _clipped_coords.size()-1; i++)
		{
			cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_coords[i])), viewport->transformY(_window->unormalize_y(_clipped_coords[i])));

			cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_coords[i + 1])), viewport->transformY(_window->unormalize_y(_clipped_coords[i + 1])));
			//cairo_stroke(_cr);

		}
		cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_coords[0])), viewport->transformY(_window->unormalize_y(_clipped_coords[0])));
		//cairo_stroke(_cr);
	}
}

Vector Polygon::getCenter()
{
	//Vector sum = _position;
	Vector sum = Vector(0,0);
	for (auto vector : _coords)
	{
		sum += vector;
	}

	return sum / static_cast<float>(_coords.size());
}

void Polygon::transform(Transformation & transformation)
{
	//_position = transformation.transformPoint(_position);
	for (size_t i = 0; i < _coords.size(); i++)
	{
		_coords[i] = transformation.transformPoint(_coords[i]);
	}

	updateWindow();
}

void Polygon::updateWindow()
{
	//_position_window = _window->normalize(_position);
	
	for (size_t i = 0; i < _coords.size(); i++)
	{
		_coords_window[i] = _window->normalize(_coords[i]);
	}
	clip();
}

void Polygon::clip()
{
	if (_coords.size() > 0)
	{
		_clipped_coords.clear();
		for (int i = 0; i < _coords.size(); i++)
		{
			Vector v_inicial = _coords_window[i];
			Vector v_final = _coords_window[(i + 1) % _coords.size()];
			unsigned int first_region = getCSRegion(_coords_window[i]);
			unsigned int final_region = getCSRegion(_coords_window[(i + 1)%_coords.size()]);

			if (!(first_region | final_region)) //both inside window
			{
				_clipped_coords.push_back(_coords_window[i]);
			}
			else if (!(first_region & final_region)) // if they're not both completely outside
			{
				CSClip(v_inicial, v_final);

				if (!first_region | !final_region) // if any inside
				{

					if (first_region)
					{
						_clipped_coords.push_back(v_inicial);
					}
					else
					{
						_clipped_coords.push_back(_coords_window[i]);
						_clipped_coords.push_back(v_final);
					}
				}
				else
				{
					_clipped_coords.push_back(v_inicial);
					_clipped_coords.push_back(v_final);
					
				}
			}
		}
	}
}

void Polygon::CSClip(Vector &v_initial, Vector &v_final)
{

	unsigned int region_initial = getCSRegion(v_initial);
	unsigned int region_final = getCSRegion(v_final);
	unsigned int region = region_initial | region_final;
	_visible = true;

	if (region)
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
		}
	}
}



unsigned int Polygon::getCSRegion(Vector &vector)
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

Vector Polygon::clipCSLine(unsigned int &region, Vector &vector1, float coeficient)
{
	Vector ret = vector1;
	if (region & CS_LEFT)
	{
		ret.x = -1.f;
		ret.y = coeficient*(-1.f - vector1.x) + vector1.y;


	}
	if (region & CS_RIGHT)
	{
		ret.x = 1.f;
		ret.y = coeficient*(1.f - vector1.x) + vector1.y;
	}
	if (region & CS_BOTTOM)
	{
		ret.y = -1.f;
		ret.x = vector1.x + 1.f / coeficient * (-1.f - vector1.y);
	}
	if (region & CS_TOP)
	{
		ret.y = 1.f;
		ret.x = vector1.x + 1.f / coeficient * (1.f - vector1.y);
	}
	return ret;
}
