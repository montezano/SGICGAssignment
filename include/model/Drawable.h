/*
 * Drawable.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_DRAWABLE_H_
#define SRC_MODEL_DRAWABLE_H_

#include <gtk/gtk.h>

#include "util/Vector.h"

class Drawable {

public:

	Drawable(const gchar *nome, double inicial_x, double inicial_y);
	Drawable(const gchar *nome, double inicial_x, double inicial_y);
	Drawable(const gchar *nome, Vector vector);
	virtual ~Drawable();

	virtual void draw(cairo_t* cr) = 0;
	Vector getPosition();

protected:
	const gchar *_nome;
	const gchar *_tipo;
	Vector _position;

};

#endif /* SRC_MODEL_DRAWABLE_H_ */
