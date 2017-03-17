/*
 * Drawable.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_DRAWABLE_H_
#define SRC_MODEL_DRAWABLE_H_

#include <gtk/gtk.h>
#include <string>
#include "Viewport.h"
#include "util/Vector.h"

class Drawable
{

public:

	Drawable(const gchar *nome, float inicial_x, float inicial_y);
	Drawable(const gchar *nome, Vector vector);
	virtual ~Drawable();

	virtual void draw(cairo_t *_cr, Viewport *viewport) = 0;
	Vector getPosition();
	void setTipo(const gchar* tipo);
	const gchar* getTipo();
	const gchar* getNome();

protected:
	std::string _nome;
	const gchar *_tipo;
	Vector _position;
	//cairo_t *_cr;



};

#endif /* SRC_MODEL_DRAWABLE_H_ */
