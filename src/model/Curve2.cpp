#include "Curve2.h"
#include "Viewport.h"


 Curve2::Curve2(const gchar * nome, std::vector<Vector> points, Windowport *window) :
 	 Polygon(nome,window),
 	 _points(points)
 {	 
	calculateCurve();
	_coords_window.resize(_coords.size());
	 updateWindow();

 }

void Curve2::calculateCurve() {

  double t[4];

  for (double i = 0; i < 1; i += 0.0001) {
    t[0] = pow(i, 3);
    t[1] = pow(i, 2);
    t[2] = pow(i, 1);
    t[3] = 1;

    double tMb[4];
   
    for (int jb = 0; jb < 4; jb++) {
      tMb[jb] = 0;
      for (int ja = 0; ja < 4; ja++) {
        tMb[jb] += t[ja] * mb[ja][jb];
      }
    }

    float x = 0;
    for (int i = 0; i < 4; i++) {
      x += tMb[i] * _points.at(i).x;
    }
    float y = 0;
    for (int i = 0; i < 4; i++) {
      y += tMb[i] * _points.at(i).y;
    }

    _coords.push_back(Vector(x,y));
  }
}

void Curve2::draw(cairo_t *_cr, Viewport *viewport) {
	if (_clipped_coords.size() > 0)
	{

	cairo_move_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_coords[0])), viewport->transformY(_window->unormalize_y(_clipped_coords[0])));
	for (size_t i = 0; i < _clipped_coords.size()-1; i++)
	{
		cairo_line_to(_cr, viewport->transformX(_window->unormalize_x(_clipped_coords[i])), viewport->transformY(_window->unormalize_y(_clipped_coords[i])));
	}
	cairo_stroke(_cr);
}	
}

