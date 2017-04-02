#ifndef __COMMAND_H__
#define __COMMAND_H__

class Command
{
public:
  virtual void execute(void *data) = 0;
};

#endif //__COMMAND_H__
