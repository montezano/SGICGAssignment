#ifndef __CLIPPING_H__
#define __CLIPPING_H__

#include "Command.h"
#include "Vector.h"

/////////////////////////////////////////////
// CLIPPING
/////////////////////////////////////////////
class Clipping : public Command
{
public:
	Clipping(Vector *initial_point, Vector *final_point);
	virtual void execute(void * data) = 0;
protected:
	Vector *_initial_point;
	Vector *_final_point;
};

/////////////////////////////////////////////
// POINT CLIPPING
/////////////////////////////////////////////
class PointClipping : public Clipping
{
public:
	PointClipping(Vector *initial_point, Vector *final_point);
	virtual void execute(void * data);
};

/////////////////////////////////////////////
// COHEN SUTHERLAND	 CLIPPING
/////////////////////////////////////////////
class CSClipping : public Clipping
{
public:
	CSClipping(Vector *initial_point, Vector *final_point);
	virtual void execute(void * data);

private:
	unsigned int getRegion(Vector &vector);
	Vector clip(unsigned int &placement, Vector &vector1, int coeficient);
};


#endif //__CLIPPING_H__
