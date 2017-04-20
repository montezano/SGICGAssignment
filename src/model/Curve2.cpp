#include "Curve2.h"
#include "Viewport.h"

 Curve2::Curve2(const gchar * nome, std::vector<Vector> points, Windowport *window) :
	 Polygon(nome,window),
	 _points(points)
 {	 
	_rate = (float)0.01;
	_tipo = "curva";
	//calcBezierCurve();
	calcBSplineCurve();
	_coords_window.resize(_coords.size());
	updateWindow();
 }

void Curve2::calcBezierCurve() {

  float t[4];

  for (float i = 0; i < 1; i += _rate) {
	t[0] = pow(i, 3);
	t[1] = pow(i, 2);
	t[2] = pow(i, 1);
	t[3] = 1;

	float tMb[4];
   
	for (int jb = 0; jb < 4; jb++) {
	  tMb[jb] = 0;
	  for (int ja = 0; ja < 4; ja++) {
		tMb[jb] += t[ja] * _mb[ja][jb];
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

void Curve2::calcBSplineCurve()
{

	int sub_curves_count = _points.size() - 3;

	float aux_x[4];
	float aux_y[4];

	prepareInitialDiferences();
	


	for (int i = 0; i < sub_curves_count; i++)
	{
		aux_x[0] = _points[i].x;	aux_y[0] = _points[i].y;
		aux_x[1] = _points[i+1].x;	aux_y[1] = _points[i+1].y;
		aux_x[2] = _points[i+2].x;	aux_y[2] = _points[i+2].y;
		aux_x[3] = _points[i+3].x;	aux_y[3] = _points[i+3].y;

		//Calculating the coeficients
		float cx[4], cy[4], fx[4], fy[4];

		cx[0] = _mbs[0] * aux_x[0] + _mbs[1] * aux_x[1] + _mbs[2] * aux_x[2] + _mbs[3] * aux_x[3];
		cx[1] = _mbs[4] * aux_x[0] + _mbs[5] * aux_x[1] + _mbs[6] * aux_x[2] + _mbs[7] * aux_x[3];
		cx[2] = _mbs[8] * aux_x[0] + _mbs[9] * aux_x[1] + _mbs[10] * aux_x[2] + _mbs[11] * aux_x[3];
		cx[3] = _mbs[12] * aux_x[0] + _mbs[13] * aux_x[1] + _mbs[14] * aux_x[2] + _mbs[15] * aux_x[3];

		cy[0] = _mbs[0] * aux_y[0] + _mbs[1] * aux_y[1] + _mbs[2] * aux_y[2] + _mbs[3] * aux_y[3];
		cy[1] = _mbs[4] * aux_y[0] + _mbs[5] * aux_y[1] + _mbs[6] * aux_y[2] + _mbs[7] * aux_y[3];
		cy[2] = _mbs[8] * aux_y[0] + _mbs[9] * aux_y[1] + _mbs[10] * aux_y[2] + _mbs[11] * aux_y[3];
		cy[3] = _mbs[12] * aux_y[0] + _mbs[13] * aux_y[1] + _mbs[14] * aux_y[2] + _mbs[15] * aux_y[3];


		fx[0] = _e[0] * cx[0] + _e[1] * cx[1] + _e[2] * cx[2] + _e[3] * cx[3];
		fx[1] = _e[4] * cx[0] + _e[5] * cx[1] + _e[6] * cx[2] + _e[7] * cx[3];
		fx[2] = _e[8] * cx[0] + _e[9] * cx[1] + _e[10] * cx[2] + _e[11] * cx[3];
		fx[3] = _e[12] * cx[0] + _e[13] * cx[1] + _e[14] * cx[2] + _e[15] * cx[3];

		fy[0] = _e[0] * cy[0] + _e[1] * cy[1] + _e[2] * cy[2] + _e[3] * cy[3];
		fy[1] = _e[4] * cy[0] + _e[5] * cy[1] + _e[6] * cy[2] + _e[7] * cy[3];
		fy[2] = _e[8] * cy[0] + _e[9] * cy[1] + _e[10] * cy[2] + _e[11] * cy[3];
		fy[3] = _e[12] * cy[0] + _e[13] * cy[1] + _e[14] * cy[2] + _e[15] * cy[3];


		int n = static_cast<int>(1 / _rate + 1);

		_coords.push_back(Vector(fx[0], fy[0]));

		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				fx[k] = fx[k] + fx[k + 1];
				fy[k] = fy[k] + fy[k + 1];
			}

			_coords.push_back(Vector(fx[0], fy[0]));
			
		}
	}
}

void Curve2::prepareInitialDiferences()
{
	_e[0] = 0;				_e[1] = 0;				_e[2] = 0;		_e[3] = 1;
	_e[4] = pow(_rate, 3);	_e[5] = pow(_rate, 2);	_e[6] = _rate;	_e[7] = 0;
	_e[8] = 6*_e[4];		_e[9] = 2*_e[5];		_e[10] = 0;		_e[11] = 0;
	_e[12] = _e[8];			_e[13] = 0;				_e[14] = 0;		_e[15] = 0;
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

const float Curve2::_mb[4][4] = {	{ -1,  3, -3, 1 },
									{  3, -6,  3, 0 },
									{ -3,  3,  0, 0 },
									{  1,  0,  0, 0 }};

const float Curve2::_mbs[16] = {   (-1/6.f),  (1/2.f), (-1/2.f), (1/6.f),
									(1/2.f),   (-1.f),  (1/2.f),   (0.f),
								   (-1/2.f),    (0.f),  (1/2.f),   (0.f),
									(1/6.f),  (2/3.f),  (1/6.f),   (0.f) };
float Curve2::_e[16];