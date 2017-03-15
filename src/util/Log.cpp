#include "util/Log.h"

Log::Log()
{
	_position = "position\t|x\t|y\n";
	_position_row = "\t\t\t";
}
void Log::onNotify(Drawable * draw, Events event)
{
	std::string message;
	switch (event)
	{
	case ADD_DRAWABLE:
		//message = "ADD " + draw->getTipo() + " : |x\t|y\n|";
		g_print("ADD %s, name: %s - position x: %f |y: %f\n",draw->getTipo(), draw->getNome(), draw->getPosition().x, draw->getPosition().y);
		break;
	case REMOVE_DRAWABLE:
		g_print("REMOVE %s, name: %s - position x: %f |y: %f\n", draw->getTipo(), draw->getNome(), draw->getPosition().x, draw->getPosition().y);
		break;

	}
}
