#include "util/Log.h"

Log::Log()
{
	_position = "position\t|x\t|y\n";
	_position_row = "\t\t\t";
}
void Log::onNotify(void * data, Events event)
{
	std::string message;
	switch (event)
	{
	case ADD_DRAWABLE:
		//message = "ADD " + draw->getTipo() + " : |x\t|y\n|";
		g_print("ADD %s, name: %s - position x: %f |y: %f\n",
			static_cast<Drawable*>(data)->getTipo(),
			static_cast<Drawable*>(data)->getNome(),
			static_cast<Drawable*>(data)->getPosition().x,
			static_cast<Drawable*>(data)->getPosition().y);
		break;
	case REMOVE_DRAWABLE:
		g_print("REMOVE %s, name: %s - position x: %f |y: %f\n",
			static_cast<Drawable*>(data)->getTipo(),
			static_cast<Drawable*>(data)->getNome(),
			static_cast<Drawable*>(data)->getPosition().x,
			static_cast<Drawable*>(data)->getPosition().y);
		break;
	case VIEWPORT_MOVE_VERTICAL:
		g_print("VIEWPORT move up\n");

	}
}
