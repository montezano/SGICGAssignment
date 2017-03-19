#include "Viewport.h"

#define PIXEL_AREA_MIN 1000



Viewport::Viewport()
{
	windowX = -300;
	windowY = -300;
	windowW = 600;
	windowH = 600;
}

Viewport::~Viewport()
{

}

float Viewport::transformX(float xw) {
  return (((float)xw - (float)windowX)/(float)windowW ) * (float)ViewportX;
}

float Viewport::transformY(float yw) {
  return (1 - (((float)yw - (float)windowY)/(float)windowH)) * (float)ViewportY;
}

Vector Viewport::transfor(Vector & vector)
{
	return Vector(transformX(vector.x), transformY(vector.y));
}


void Viewport::zoom(float factor) {
  float cX, cY;
  if (((windowW * windowH) / (factor * factor)) <= PIXEL_AREA_MIN) {
	return;
  }
  cX = windowW / 2 + windowX;
  cY = windowH / 2 + windowY;
  windowW /= factor;
  windowH /= factor;
  windowX = cX - (windowW / 2);
  windowY = cY - (windowH / 2);
  notify(NULL, (factor > 0) ? Events::VIEWPORT_ZOOM_IN: Events::VIEWPORT_ZOOM_OUT);
}

void Viewport::moveHorizontal(float factor) {
  windowX += factor * 100;
  notify(NULL, Events::VIEWPORT_MOVE_HORIZONTAL);
}

void Viewport::moveVertical(float factor) {
  windowY += factor * 100;
  notify(NULL, Events::VIEWPORT_MOVE_VERTICAL);
}


