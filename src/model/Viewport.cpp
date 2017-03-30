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
	return Vector(transformX(vector.x), transformY(vector.y));
}
//
//
//void Viewport::zoom(float factor) {
//  float cX, cY;
//  if (((windowW * windowH) / (factor * factor)) <= PIXEL_AREA_MIN) {
//	return;
//  }
//  cX = windowW / 2 + windowX;
//  cY = windowH / 2 + windowY;
//  windowW /= factor;
//  windowH /= factor;
//  windowX = cX - (windowW / 2);
//  windowY = cY - (windowH / 2);
//  notify(NULL, (factor > 0) ? Events::WINDOW_ZOOM_IN: Events::WINDOW_ZOOM_OUT);
//}
//
//void Viewport::moveHorizontal(float factor) {
//  windowX += factor * 100;
//  notify(NULL, Events::WINDOW_MOVE_HORIZONTAL);
//}
//
//void Viewport::moveVertical(float factor) {
//  windowY += factor * 100;
//  notify(NULL, Events::WINDOW_MOVE_VERTICAL);
//}
