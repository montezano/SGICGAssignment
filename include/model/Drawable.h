/*
 * Drawable.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */


#ifndef SRC_MODEL_DRAWABLE_H_
#define SRC_MODEL_DRAWABLE_H_

class Command;

#include <gtk/gtk.h>
#include <string>
#include "Viewport.h"
#include "Vector.h"
#include "Transformation.h"
#include "Windowport.h"
#include "Command.h"

class Drawable
{

public:

	Drawable(const gchar *nome, float inicial_x, float inicial_y, Windowport *window);
	Drawable(const gchar *nome, Vector vector, Windowport *window);
	virtual ~Drawable();

	virtual void draw(cairo_t *_cr, Viewport *viewport) = 0;
	Vector getPosition();
	Vector getPositionWindow();
	void setTipo(const gchar* tipo);
	const gchar* getTipo();
	const gchar* getNome();
	virtual Vector getCenter() = 0;
	virtual void transform(Transformation &transformation) = 0;
	virtual void updateWindow() = 0;


protected:

	std::string _nome;
	const gchar *_tipo;
	Vector _position;
	Vector _position_window;
	Windowport *_window;
	Command *_clipping;
	//cairo_t *_cr;



};

#endif /* SRC_MODEL_DRAWABLE_H_ */
