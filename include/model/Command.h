#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "Drawable.h"

class Command
{
public:
  virtual void execute(Drawable &drawable) = 0;
};

#endif //__COMMAND_H__
