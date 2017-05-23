#include "Surface.h"
#include "Viewport.h"
#include <cstring>
Surface::Surface(const gchar * nome, std::vector<std::vector<Vector*>> matrix, Windowport *window, bool type) :
	 Object3D(nome,window),
        _matrix(matrix),
        _type(type)
 {
	_tipo = "superficie";
        _sStep = 0.1;
        _tStep = 0.01;
        _points = std::vector<std::vector<Vector*>>();
        calcSurface();
	updateWindow();
 }

 Surface::~Surface()
 {
	 for (std::vector<Vector*> it : _matrix)
	 {
             for (Vector *v : it)
		 delete (v);
	 }
	 _matrix.clear();
 }
 
void Surface::calculateG(int lines, int columns, std::vector<std::vector<float>>* m, Surface::coords coord){
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++) {
        switch(coord) {
            case Surface::coords::X: m->at(i).at(j) = _matrix.at(i).at(j)->x;
                  break;
            case Surface::coords::Y: m->at(i).at(j) = _matrix.at(i).at(j)->y;
                  break;
            case Surface::coords::Z: m->at(i).at(j) = _matrix.at(i).at(j)->z;
                  break;
    }
    }
  }
}

void Surface::calcSurface(){
     
  int lines = _matrix.size();
  int columns = _matrix.at(0).size();

  std::vector<std::vector<float>> gX;  
  gX.resize(lines,std::vector<float>(columns,0));
  std::vector<std::vector<float>> gY;
  gY.resize(lines,std::vector<float>(columns,0));
  std::vector<std::vector<float>> gZ;  
  gZ.resize(lines,std::vector<float>(columns,0));
  
  calculateG(lines, columns, &gX, Surface::coords::X);
  calculateG(lines, columns, &gY, Surface::coords::Y);
  calculateG(lines, columns, &gZ, Surface::coords::Z);
  
  for (int m = 3; m < lines; m++) {
    // Coeficientes C
    float Cx[4][4], Cy[4][4], Cz[4][4];
    float tmpx[4][4], tmpy[4][4], tmpz[4][4];
    
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        tmpx[i][j] = 0; tmpy[i][j] = 0; tmpz[i][j] = 0;
        for (int k = 0; k < 4; k++) {
            if(_type){
                tmpx[i][j] += _mbs[i][k] * gX[k+m-3][j+m-3];
                tmpy[i][j] += _mbs[i][k] * gY[k+m-3][j+m-3];
                tmpz[i][j] += _mbs[i][k] * gZ[k+m-3][j+m-3];
            } else {
                tmpx[i][j] += _ms[i][k] * gX[k+m-3][j+m-3];
                tmpy[i][j] += _ms[i][k] * gY[k+m-3][j+m-3];
                tmpz[i][j] += _ms[i][k] * gZ[k+m-3][j+m-3];
            }
        }
      }
    }
    
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        Cx[i][j] = 0; Cy[i][j] = 0; Cz[i][j] = 0;
        for (int k = 0; k < 4; k++) {
            if(_type) {
                Cx[i][j] += tmpx[i][k] * _mbs[j][k];
                Cy[i][j] += tmpy[i][k] * _mbs[j][k];
                Cz[i][j] += tmpz[i][k] * _mbs[j][k];
            } else {
                Cx[i][j] += tmpx[i][k] * _ms[j][k];
                Cy[i][j] += tmpy[i][k] * _ms[j][k];
                Cz[i][j] += tmpz[i][k] * _ms[j][k];
            }
        }
      }
    }
    
    float t[4];
    float s[4];
    float tmpCx[4], tmpCy[4], tmpCz[4];
    float x, y, z;
    std::vector<Vector*> tmpVector;
    
    // Calculo do t
    t[3] = 1.0;
    s[3] = 1.0;
    for (float f = 0.0; f <= 1.001; f+=_sStep) {
      t[2] = f;
      t[1] = t[2] * t[2];
      t[0] = t[1] * t[2];
      
      for (int i = 0; i < 4; i++) {
        tmpCx[i] = 0; tmpCy[i] = 0; tmpCz[i] = 0;
        for (int j = 0; j < 4; j++) {
          tmpCx[i] += Cx[i][j] * t[j];
          tmpCy[i] += Cy[i][j] * t[j];
          tmpCz[i] += Cz[i][j] * t[j];
        }
      }
      tmpVector = std::vector<Vector*>();
      for (float g = 0.0; g <= 1.001; g+=_tStep) {
        s[2] = g;
        s[1] = s[2] * s[2];
        s[0] = s[1] * s[2];
        x = 0; y = 0; z = 0;
        for (int i = 0; i < 4; i++) {
          x += s[i] * tmpCx[i];
          y += s[i] * tmpCy[i];
          z += s[i] * tmpCz[i];
        }
        Vector *p = new Vector(x, y, z);
        tmpVector.push_back(p);
      }
      _points.push_back(tmpVector);
    }
    
    // Calculo do s
    for (float f = 0.0; f <= 1.001; f+=_sStep) {
      t[2] = f;
      t[1] = t[2] * t[2];
      t[0] = t[1] * t[2];
      
      for (int i = 0; i < 4; i++) {
        tmpCx[i] = 0; tmpCy[i] = 0; tmpCz[i] = 0;
        for (int j = 0; j < 4; j++) {
          tmpCx[i] += t[j] * Cx[j][i];
          tmpCy[i] += t[j] * Cy[j][i];
          tmpCz[i] += t[j] * Cz[j][i];
        }
      }
      tmpVector = std::vector<Vector*>();
      for (float g = 0.0; g <= 1.001; g+=_tStep) {
        s[2] = g;
        s[1] = s[2] * s[2];
        s[0] = s[1] * s[2];
        x = 0; y = 0; z = 0;
        for (int i = 0; i < 4; i++) {
          x += tmpCx[i] * s[i];
          y += tmpCy[i] * s[i];
          z += tmpCz[i] * s[i];
        }
        Vector *p = new Vector(x, y, z);
        tmpVector.push_back(p);
      }
      _points.push_back(tmpVector);
    }
  }
  //Transforma a matriz de pontos em linhas para tratar como obj 3D
  this->pointsToLine();
  
 }
 
 void Surface::pointsToLine(){
  Vector *init, *fim;
  int i = 0;
  for (auto elem : _points) {
      i++;
      init = new Vector(elem.at(i)->x,elem.at(i)->y,elem.at(i)->z);
      for (auto item : elem) {
          fim = new Vector(item->x, item->y, item->z);
          _object.push_back(new Line("",init,fim,_window));
          init = fim;
        }
    }
 }
 
 const float Surface::_mbs[4][4] = {
    {-1.0/6.f,  3.0/6.f, -3.0/6.f, 1.0/6.f},
    { 3.0/6.f, -6.0/6.f,  3.0/6.f, 0.0/6.f},
    {-3.0/6.f,  0.0/6.f,  3.0/6.f, 0.0/6.f},
    { 1.0/6.f,  4.0/6.f,  1.0/6.f, 0.0/6.f}
  };
 
 const float Surface::_ms[4][4] = {
    {1.f,  3.f, -3.f, 1.f},
    { 3.f, -6.f,  3.f, 0.f},
    {-3.f,  0.f,  3.f, 0.f},
    { 1.f,  4.f,  1.f, 0.f}
 };