#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "util/Event.h"

class Observer
{
public:
	virtual ~Observer() {};
	virtual void onNotify(void *data, Events event) = 0;

};



#endif // !__OBSERVER_H__
