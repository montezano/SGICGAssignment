/*
 * Drawable.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Drawable.h"

Drawable::Drawable(const gchar *nome, const gchar *tipo, gdouble inicial_x, gdouble inicial_y) {
	// TODO Auto-generated constructor stub
	this->nome = nome;
	this->tipo = tipo;
	this->inicial_x = inicial_x;
	this->inicial_y = inicial_y;

}

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

gdouble Drawable::getX() {
	return this->inicial_x;
}

gdouble Drawable::getY() {
	return this->inicial_y;
}
