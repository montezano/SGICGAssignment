#include "Clipping.h"

#include "Point.h"
#include "Line.h"
#include "Polygon.h"

#define CS_MIDDLE		0
#define CS_TOP			1 << 1
#define CS_BOTTOM		1 << 2
#define CS_RIGHT		1 << 3
#define CS_LEFT			1 << 4
#define CS_TOP_LEFT		CS_TOP | CS_LEFT
#define CS_TOP_RIGHT	CS_TOP | CS_RIGHT
#define CS_BOTTOM_LEFT	CS_BOTTOM | CS_LEFT
#define CS_BOTTOM_RIGHT	CS_BOTTOM | CS_RIGHT


Clipping::Clipping(Vector * initial_point, Vector * final_point)
{
	_initial_point = initial_point;
	_final_point = final_point;
}

/////////////////////////////////////////////
// POINT CLIPPING
/////////////////////////////////////////////
PointClipping::PointClipping(Vector * initial_point, Vector * final_point) :
	Clipping(initial_point, final_point)
{
}


CSClipping::CSClipping(Vector * initial_point, Vector * final_point) :
	Clipping(initial_point, final_point)
{
}

void PointClipping::execute(void * data)
{
	Point *point = static_cast<Point*>(data);
	Vector vector = point->getPositionWindow();
	if (vector.x > -1.f && vector.y > -1.f && vector.x < 1.f && vector.y < 1.f)
	{
		point->setVisible(true);
	}
	else
	{
		point->setVisible(false);
	}
}



/////////////////////////////////////////////
// COHEN SUTHERLAND	 CLIPPING
/////////////////////////////////////////////
void CSClipping::execute(void * data)
{
	Line *line = static_cast<Line*>(data);
	Vector v_initial = line->getPositionWindow();
	Vector v_final = line->getFinalPositionWindow();
	unsigned int region_initial = getRegion(v_initial);
	unsigned int region_final = getRegion(v_final);
	unsigned int region = region_initial | region_final;

	if (!region_initial && !region_final)
	{
		line->setClippedPosition(v_initial, v_final);
	}
	else
	{
		if (!(region_initial & region_final))
		{
			return; //setVisible(false);
		}
		else
		{
			int m = (v_initial.y - v_final.y) / (v_initial.x - v_final.y);
			if (region_initial)
			{
				v_initial = clip(region_initial, v_initial, m);
			}
			if (region_final)
			{
				v_final = clip(region_final, v_final, m);
			}
			line->setClippedPosition(v_initial, v_final);
		}
	}

}

unsigned int CSClipping::getRegion(Vector & vector)
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

Vector CSClipping::clip(unsigned int &region, Vector &vector1, int coeficient)
{
	Vector ret = vector1;
	if (region & CS_LEFT)
	{
		ret.x = _initial_point->x;
		ret.y = coeficient*(_final_point->x - vector1.x) + vector1.y;

	}
	if (region & CS_RIGHT)
	{
		ret.x = _final_point->x;
		ret.y = coeficient*(_final_point->x - vector1.x) + vector1.y;
	}
	if (region & CS_BOTTOM)
	{
		ret.y = _final_point->y;
		ret.x = vector1.x + 1 / coeficient * (_final_point->y - vector1.y);
	}
	if (region & CS_TOP)
	{
		ret.y = _initial_point->y;
		ret.x = vector1.x + 1 / coeficient * (_initial_point->y - vector1.y);
	}
	return ret;
}


