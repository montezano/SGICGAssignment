/*
 * Drawable.h
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#ifndef SRC_MODEL_DRAWABLE_H_
#define SRC_MODEL_DRAWABLE_H_
#include <gtk/gtk.h>

class Drawable {

public:
	Drawable(const gchar *nome, const gchar *tipo, gdouble inicial_x, gdouble inicial_y);
	virtual ~Drawable();

    virtual void draw(cairo_t* cr) = 0;
    gdouble getX();
    gdouble getY();

private:
	const gchar *nome;
	const gchar *tipo;
	gdouble inicial_x;
	gdouble inicial_y;

};

#endif /* SRC_MODEL_DRAWABLE_H_ */
