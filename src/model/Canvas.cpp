#include "model/Canvas.h"

Canvas::Canvas()
{
}

Canvas::~Canvas()
{

}

void Canvas::addLine(char *nome, Vector v_inicial, Vector v_final)
{
  _canvas.push_back(static_cast<Drawable*>(new Line(nome, v_inicial, v_final)));
}

void Canvas::drawCanvas()
{
  for(auto drawable: _canvas.begin())
  {
    
  }
}
