#include "Drawable.h"

Drawable::Drawable(const gchar * nome, float inicial_x, float inicial_y, Windowport *window) :
	_nome(nome),
	_position(Vector(inicial_x, inicial_y)),
	_position_window(Vector(inicial_x, inicial_y)),
	_visible(true)
 {
	 _window = window;
 }

 Drawable::Drawable(const gchar * nome, Vector vector, Windowport *window) :
	_nome(nome),
	_position(vector),
	_position_window(vector),
	_visible(true)
 {
	 _window = window;
 }

 Drawable::~Drawable()
{
}

 Vector Drawable::getPosition()
 {
	 return _position;
 }

 Vector Drawable::getPositionWindow()
 {
	 return _position_window;
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