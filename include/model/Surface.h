/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Surface.h
 * Author: luizurias
 *
 * Created on 21 de Maio de 2017, 13:05
 */

#ifndef SURFACE_H
#define SURFACE_H

#include "Object3D.h"
#include <vector>

class Surface : public Object3D {
public:
	Surface(const gchar *nome, std::vector<std::vector<Vector*>> points, Windowport *window, bool type = true);
	virtual ~Surface();  

private:
    enum coords {
        X = 1,
        Y = 2,
        Z = 3
    };
	void calcSurface();
        void calculateG(int lines, int columns, std::vector<std::vector<float>>* m, Surface::coords coord);
        void pointsToLine();
        std::vector<Vector*> drawFwdDiff(int n, const float c_x[4], const float c_y[4], const float c_z[4]);
	std::vector<std::vector<Vector*>> _matrix;
        std::vector<std::vector<Vector*>> _points;
        std::vector<std::vector<Vector*>> _points_window;
        bool _type; //true = b-spline; false = bezier
	float _sStep;
        float _tStep;
        static const float _mbs[4][4];
        static const float _ms[4][4];

};


#endif /* SURFACE_H */

