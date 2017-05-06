#include "Viewport.h"

//#define PIXEL_AREA_MIN 1000



Viewport::Viewport()
{
	windowX = -300;
	windowY = -300;
	windowW = 600;
	windowH = 600;
	ViewportX = 600;
	ViewportY = 600;
}

Viewport::~Viewport()
{

}

void Viewport::setSize(Vector vector)
{
	windowX = -(vector.x / 2);
	windowY = -(vector.y / 2);
	windowW = vector.x;
	windowH = vector.y;
	ViewportX = vector.x;
	ViewportY = vector.y;
}

float Viewport::transformX(float xw) {
  return ((xw - windowX)/windowW ) * ViewportX;
}

float Viewport::transformY(float yw) {
  return (1 - ((yw - windowY)/windowH)) * ViewportY;
}

Vector Viewport::transform(Vector & vector)
{
	return Vector(transformX(vector.x), transformY(vector.y), DUMMY);
}