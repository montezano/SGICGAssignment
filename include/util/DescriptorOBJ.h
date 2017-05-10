
#ifndef DESCRIPTOROBJ_H
#define DESCRIPTOROBJ_H

class DescriptorOBJ;

#include <gtk/gtk.h>
#include <list>
#include <vector>
#include "Point.h"
#include "Canvas.h"
#include "Line.h"
#include "Polygon.h"
#include "Window.h"
#include "Object3D.h"
#include "Curve2.h"

class DescriptorOBJ {
private:
//  static std::list<Point*> *readPoints(const std::vector<Point*> *points, const char *line);
//  static std::list<int> *readPointsNumber(const char *line);
public:
    DescriptorOBJ(const char *fileName, Windowport* window);
     std::vector<Drawable*> *load();
    const char* _fileName;
    Windowport* _window;
};





#endif /* DESCRIPTOROBJ_H */

