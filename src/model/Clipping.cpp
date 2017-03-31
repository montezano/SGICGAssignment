#include "Clipping.h"

#include "Point.h"

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
