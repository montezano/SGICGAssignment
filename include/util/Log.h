#ifndef __LOG_H__
#define __LOG_H__

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

#include "model/Drawable.h"
#include "util/Event.h"
#include "util/Observer.h"


class Log : public Observer
{
public:
	Log();
	virtual void onNotify(Drawable *draw, Events event);

private:
	std::string _position;
	std::string _position_row;
};
#endif // !__LOG_H__
