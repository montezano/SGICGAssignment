#ifndef __CLIPPING_H__
#define __CLIPPING_H__

#include "Command.h"

class PointClipping : public Command
{
public:
	PointClipping() {};
	virtual void execute(Drawable &drawable);
};


#endif //__CLIPPING_H__
