/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Viewport.h
 * Author: luizurias
 *
 * Created on 15 de Março de 2017, 16:03
 */

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <gtk/gtk.h>

#include "Subject.h"
#include "Vector.h"

class Viewport : public Subject
{
public:
	Viewport();
	virtual ~Viewport();
	float ViewportX = 600, ViewportY = 600;

	void setSize(Vector vector);
	


	float transformX(float xw);
	float transformY(float yw);
	Vector transform(Vector &vector);
 // 
	//void zoom(float factor);
	//void moveHorizontal(float factor);
	//void moveVertical(float factor);

private:
	float windowX, windowY;
	float windowW, windowH;
};


#endif /* VIEWPORT_H */

