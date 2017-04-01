#ifndef __CLIPPING_H__
#define __CLIPPING_H__

#include "Command.h"

class PointClipping : public Command
{
public:
	virtual void execute(Drawable &drawable);
};

class CSClipping : public Command
{
public:
	virtual void execute(Drawable &drawable);

private:
	unsigned int getRegion(Vector &vector);
	Vector clip(unsigned int &placement, Vector &vector1, int coeficient);
};


#endif //__CLIPPING_H__
