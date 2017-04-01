#include "Clipping.h"

#include "Point.h"
#include "Line.h"

#define CS_MIDDLE		0
#define CS_TOP			1 << 1
#define CS_BOTTOM		1 << 2
#define CS_RIGHT		1 << 3
#define CS_LEFT			1 << 4
#define CS_TOP_LEFT		CS_TOP | CS_LEFT
#define CS_TOP_RIGHT	CS_TOP | CS_RIGHT
#define CS_BOTTOM_LEFT	CS_BOTTOM | CS_LEFT
#define CS_BOTTOM_RIGHT	CS_BOTTOM | CS_RIGHT



/////////////////////////////////////////////
// POINT CLIPPING
/////////////////////////////////////////////
void PointClipping::execute(Drawable &drawable)
{
	Vector vector = drawable.getPositionWindow();
	if (vector.x > -1.f && vector.y > -1.f && vector.x < 1.f && vector.y < 1.f)
	{
		static_cast<Point&>(drawable).setVisible(true);
	}
	else
	{
		static_cast<Point&>(drawable).setVisible(false);
	}
}

/////////////////////////////////////////////
// COHEN SUTHERLAND	 CLIPPING
/////////////////////////////////////////////
void CSClipping::execute(Drawable &drawable)
{
	Line *line = dynamic_cast<Line*>(&drawable);
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
			int m = (v_initial.y - v_final.y) / (v_final.x - v_final.y);
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
	if (region & CS_LEFT)
	{

	}
	if (region & CS_RIGHT)
	{

	}
	if (region & CS_BOTTOM)
	{

	}
	if (region & CS_TOP)
	{

	}
	return Vector();
}
