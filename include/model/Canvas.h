#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <vector>

#include "util/Vector.h"
#include "model/Line.h"

class Canvas
{
public:
  Canvas();
  virtual ~Canvas();
  void addLine(char *nome, Vector v_inicial, Vector v_final);

  void drawCanvas();

private:
  std::vector<Drawable*> _canvas;

};

#endif //__CANVAS_H__
