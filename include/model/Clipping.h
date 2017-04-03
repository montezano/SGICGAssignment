//#ifndef __CLIPPING_H__
//#define __CLIPPING_H__
//
//#include <assert.h>
//
//#include "Vector.h"
//#include "Point.h"
//#include "Line.h"
//#include "Polygon.h"
//
//
///////////////////////////////////////////////
//// CLIPPING
///////////////////////////////////////////////
//class Clipping
//{
//public:
//
//	enum ClippingAlgorithm
//	{
//		POINT,
//		CS,
//		LB,
//		NICLEENIC,
//		SUTHHODG,
//		WEIL
//	};
//
//
//	static void initialize(Vector *initial_point, Vector *final_point);
//	static void clip(Point *point);
//	static void clip(Line *line);
//	static void clip(Polygon *polygon);
//
//	static void pointClip(Point *point);
//	static void CSClip(Line *line);
//
//	static void changeAlgorithm(ClippingAlgorithm alg);
//
//
//
//private:
//
//	static bool _initialized;
//	static ClippingAlgorithm _point_alg;
//	static ClippingAlgorithm _line_alg;
//	static ClippingAlgorithm _polygon_alg;
//	static Vector *_initial_point;
//	static Vector *_final_point;
//
//	static unsigned int getCSRegion(Vector &vector);
//	static Vector clipCSLine(unsigned int &placement, Vector &vector1, int coeficient);
//
//};
//
//
//#endif //__CLIPPING_H__
