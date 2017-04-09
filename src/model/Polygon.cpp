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
	std::vector<unsigned int> outside;
	Vector v_outside;
	if (_coords.size() > 0)
	{
		_clipped_coords.clear();
		for (int i = 0; i < _coords.size(); i++)
		{
			Vector v_inicial = _coords_window[i];
			Vector v_final = _coords_window[(i + 1) % _coords.size()];
			unsigned int first_region = getCSRegion(_coords_window[i]);
			unsigned int final_region = getCSRegion(_coords_window[(i + 1)%_coords.size()]);
			CSClip(v_inicial, v_final);


			if (!(first_region | final_region)) //both inside window
			{
				_clipped_coords.push_back(v_final);
			}
			else
			{
				if (!(first_region & final_region)) // if they're not both completely outside
				{

					if (!first_region | !final_region) // if any inside
					{
						if (first_region)
						{


							//handle the outside vector
							if (outside.size() > 0)
							{
								unsigned int clipped_region = getCSRegion(v_inicial);
								for (int i =0; i < outside.size(); i++)
								{
									if (outside[i] != clipped_region) //region different from the point where the line enter the window
									{
										switch (outside[i])
										{
										case CS_BOTTOM_LEFT:
											_clipped_coords.push_back(Vector(-1, -1));
											break;
										case CS_BOTTOM_RIGHT:
											_clipped_coords.push_back(Vector(1, -1));

											break;
										case CS_TOP_LEFT:
											_clipped_coords.push_back(Vector(-1, 1));

											break;
										case CS_TOP_RIGHT:
											_clipped_coords.push_back(Vector(1, 1));

											break;
										}
									}
								}
								outside.clear();

							}
							_clipped_coords.push_back(v_inicial);
							_clipped_coords.push_back(v_final);

						}
						else
						{
							_clipped_coords.push_back(v_final);

							outside.push_back(final_region);
						}
					}
					else //if none inside but any passing through
					{
						unsigned int aux_init_region = getCSRegion(v_inicial);
						unsigned int aux_final_region = getCSRegion(v_final);
						if (aux_init_region | aux_final_region)
						{
							outside.push_back(aux_init_region | aux_final_region);

						}
						else
						{
							_clipped_coords.push_back(v_inicial);
							_clipped_coords.push_back(v_final);
							outside.push_back(final_region);
						}
						

					}
				}
				else //both completely outside
				{
					outside.push_back(first_region);

					outside.push_back(final_region);
					//outside = true;
					//v_outside = v_final;
					//CSClip(v_outside, _clipped_coords[0]);
					//if(v_outside.x < -1)
					//switch (final_region)
					//{
					//case CS_BOTTOM_LEFT:
					//	v_outside = Vector(-1, -1);
					//	break;
					//case CS_BOTTOM_RIGHT:
					//	v_outside = Vector(1, -1);

					//	break;
					//case CS_TOP_LEFT:
					//	v_outside = Vector(-1, 1);

					//	break;
					//case CS_TOP_RIGHT:
					//	v_outside = Vector(1, 1);

					//	break;
					//case CS_BOTTOM:
					//	v_outside = Vector(v_final.x, -1);

					//	break;
					//case CS_TOP:
					//	v_outside = Vector(v_final.x, 1);

					//	break;
					//case CS_LEFT:
					//	v_outside = Vector(-1, v_final.y);

					//	break;
					//case CS_RIGHT:
					//	v_outside = Vector(1, v_final.y);

					//	break;

					//}
					//if (first_region)
					//{
					//	_clipped_coords.push_back(v_outside);

					//}
				}			
			}
		}
		for (int i = 0; i < outside.size(); i++)
		{
			{
				switch (outside[i])
				{
				case CS_BOTTOM_LEFT:
					_clipped_coords.push_back(Vector(-1, -1));
					break;
				case CS_BOTTOM_RIGHT:
					_clipped_coords.push_back(Vector(1, -1));

					break;
				case CS_TOP_LEFT:
					_clipped_coords.push_back(Vector(-1, 1));

					break;
				case CS_TOP_RIGHT:
					_clipped_coords.push_back(Vector(1, 1));

					break;
				}
			}
		}
		outside.clear();
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
			ret.x = x;
			ret.y = 1;
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
			ret.x = x;
			ret.y = 1;
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
			ret.x = x;
			ret.y = -1;
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
			ret.x = x;
			ret.y = -1;
		}
		break;
	}

	return ret;
}
