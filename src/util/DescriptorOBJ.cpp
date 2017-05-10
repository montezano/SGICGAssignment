#include "DescriptorOBJ.h"


DescriptorOBJ::DescriptorOBJ(const char* fileName, Windowport* window){
    _fileName = fileName;
    _window = window;
}
std::vector<Drawable*> *DescriptorOBJ::load() {
  std::vector<Drawable*> *objects = new std::vector<Drawable*>;
  std::vector<Line*> *lines = new std::vector<Line*>;
  if (_fileName == NULL) {
    return objects;
  }
  if (_fileName[0] == '\0') {
    return objects;
  }
  FILE *file = fopen(_fileName, "r");
  std::vector<Vector*> pointsList;
  Drawable *tmpObj = NULL;
  char name[150];
  char tmpLine[512];
  int ch;
  while ( (ch = fgetc(file) ) != EOF) {
    int i = 0;
    if (ch == '\n') {
      continue;
    }
    if (ch == '#') {
      while ( (ch = fgetc(file) ) != '\n') {
        if (ch == EOF) {
          break;
        }
      }
      continue;
    }
    tmpLine[i++] = ch;
    while ( (ch = fgetc(file) ) != '\n') {
      if (ch == EOF) {
        break;
      }
      if (ch == '#') {
        while ( (ch = fgetc(file) ) != '\n') {
          if (ch == EOF) {
            break;
          }
        }
        break;
      }
      if (ch == '.')
        ch = ',';
      tmpLine[i++] = ch;
    }
    tmpLine[i] = '\0';
    
    
    if (tmpLine[0] == 'o') {
       sscanf(tmpLine, "o %s", &name);

    }
    if (tmpLine[0] == 'v' && tmpLine[1] == ' ') {
      float x, y, z, nil;
      sscanf(tmpLine, "v %f %f %f %f", &x, &y, &z, &nil);
      pointsList.push_back(new Vector(x, y, z));
    }

    if (tmpLine[0] == 'l' && tmpLine[1] == ' ') {
       int a,b,c,d; 
       sscanf(tmpLine, "l %d %d %d %d", &a, &b, &c, &d);
       Line* l1 = new Line(name, pointsList.at(a-1), pointsList.at(b-1),_window);
       Line* l2 = new Line(name, pointsList.at(c-1), pointsList.at(d-1),_window);

       lines->push_back(l1);
       lines->push_back(l2);

    }
  }
  if (lines != NULL) {
    tmpObj = new Object3D(name, *lines, _window);
    g_print(tmpObj->getNome());
    objects->push_back(tmpObj);
    tmpObj = NULL;
  }
  return objects;
}