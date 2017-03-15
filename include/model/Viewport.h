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

class Viewport {
private:
  static float windowX, windowY;
  static float windowW, windowH;

public:
  const static int ViewportX = 600, ViewportY = 600;

  static float transformX(float xw);
  static float transformY(float yw);
  
  static void zoom(float factor);
  static void moveHorizontal(float factor);
  static void moveVertical(float factor);
};


#endif /* VIEWPORT_H */

