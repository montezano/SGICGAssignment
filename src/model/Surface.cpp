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
    float fineStep = 0.01;
    float croaseStep = 0.1;
    
    for (int a = 0; a < 2; a++) {
      float tStep, sStep;
      if (!a) {
        _tStep = fineStep;
        _sStep = croaseStep;
      } else {
        _tStep = croaseStep;
        _sStep = fineStep;
      }
      
      t[0] = 1.0;
      t[1] = t[0] * _tStep;
      t[2] = t[1] * _tStep;
      t[3] = t[2] * _tStep;
      
      s[0] = 1.0;
      s[1] = s[0] * _sStep;
      s[2] = s[1] * _sStep;
      s[3] = s[2] * _sStep;
      
      float mEt[4][4] = {
        {     0,      0,    0, t[0]},
        {1*t[3], 1*t[2], t[1],    0},
        {6*t[3], 2*t[2],    0,    0},
        {6*t[3],      0,    0,    0}
      };
      
      float mEs[4][4] = {
        {     0,      0,    0, s[0]},
        {1*s[3], 1*s[2], s[1],    0},
        {6*s[3], 2*s[2],    0,    0},
        {6*s[3],      0,    0,    0}
      };
      
      float mDDx[4][4], mDDy[4][4], mDDz[4][4];
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          tmpx[i][j] = 0;
          tmpy[i][j] = 0;
          tmpz[i][j] = 0;
          for (int k = 0; k < 4; k++) {
            tmpx[i][j] += mEs[i][k] * Cx[k][j];
            tmpy[i][j] += mEs[i][k] * Cy[k][j];
            tmpz[i][j] += mEs[i][k] * Cz[k][j];
          }
        }
      }
      
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          mDDx[i][j] = 0;
          mDDy[i][j] = 0;
          mDDz[i][j] = 0;
          for (int k = 0; k < 4; k++) {
            mDDx[i][j] += tmpx[i][k] * mEt[j][k];
            mDDy[i][j] += tmpy[i][k] * mEt[j][k];
            mDDz[i][j] += tmpz[i][k] * mEt[j][k];
          }
        }
      }
      if (a == 1) {
        for (int i = 0; i < 4; i++) {
          for (int j = i; j < 4; j++) {
            float tmp;
            tmp = mDDx[i][j];
            mDDx[i][j] = mDDx[j][i];
            mDDx[j][i] = tmp;
            tmp = mDDy[i][j];
            mDDy[i][j] = mDDy[j][i];
            mDDy[j][i] = tmp;
            tmp = mDDz[i][j];
            mDDz[i][j] = mDDz[j][i];
            mDDz[j][i] = tmp;
          }
        }
      }
      std::vector<Vector*> tmpVect;
      int nt, ns;
      if (a) {
        nt = 1/_sStep + 1;
        ns = 1/_tStep + 1;
      } else {
        nt = 1/_tStep + 1;
        ns = 1/_sStep + 1;
      }
      for (int i = 0; i < ns; i++) {
        tmpVect = drawFwdDiff(nt, mDDx[0], mDDy[0], mDDz[0]);
        _points.push_back(tmpVect);
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 3; k++) {
            mDDx[j][k] = mDDx[j][k] + mDDx[j+1][k];
            mDDy[j][k] = mDDy[j][k] + mDDy[j+1][k];
            mDDz[j][k] = mDDz[j][k] + mDDz[j+1][k];
          }
        }
      }
    }
  //Transforma a matriz de pontos em linhas para tratar como obj 3D
  }
  this->pointsToLine();
 
}
 
std::vector<Vector*> Surface::drawFwdDiff(int n, const float c_x[4], const float c_y[4], const float c_z[4]) {
  std::vector<Vector*> curvePoints = std::vector<Vector*>();
  float x[4], y[4], z[4];
  for (int k = 0; k < 4; k++) {
    x[k] = c_x[k];
    y[k] = c_y[k];
    z[k] = c_z[k];
  }
  curvePoints.push_back(new Vector(x[0], y[0], z[0]));
  for (int i = 0; i < n; i++) {
    x[0] += x[1];
    x[1] += x[2];
    x[2] += x[3];
    
    y[0] += y[1];
    y[1] += y[2];
    y[2] += y[3];
    
    z[0] += z[1];
    z[1] += z[2];
    z[2] += z[3];
    curvePoints.push_back(new Vector(x[0], y[0], z[0]));
  }
  return curvePoints;
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