/*
 * Drawable.cpp
 *
 *  Created on: 12 de mar de 2017
 *      Author: luizurias
 */

#include "model/Drawable.h"

 Drawable::Drawable(const gchar * nome, double inicial_x, double inicial_y) :
	 _nome(nome)
 {
	 this->_position = Vector(inicial_x, inicial_y);
 }

 Drawable::Drawable(const gchar * nome, Vector vector) :
	 _nome(nome)
 {
	 this->_position = vector;
 }

 Drawable::~Drawable()
{
}

 Vector Drawable::getPosition()
 {
	 return _position;
 }

 const gchar* Drawable::getNome(){
   return _nome.c_str();

 }

 const gchar* Drawable::getTipo(){
   return _tipo;
 }

 void Drawable::setTipo(const gchar* tipo){
   _tipo = tipo;
 }