#include "Canvas.h"

#include <assert.h>

Canvas::Canvas(Viewport *viewport, Windowport *window)
{
	assert(viewport);
	assert(window);
	_viewport = viewport;
	_window = window;
}

Canvas::Canvas()
{
}


Canvas::~Canvas()
{

}

void Canvas::setWindow(Windowport * window)
{
	assert(window);
	_window = window;
}

void Canvas::addLine(const gchar* nome, Vector inicial, Vector fim)
{
	Drawable* line = new Line(nome,inicial,fim, _window);
	line->setTipo("linha");

	_canvas.push_back(line);

	// //TESTE
	// std::vector<Vector> points;
	// points.push_back(Vector(0,0));
	// points.push_back(Vector(30,-100));
	// points.push_back(Vector(70,-150));
	// points.push_back(Vector(500,0));
	// Drawable* curve = new Curve2(nome, points, _window);
	// curve->setTipo("curva");

	// _canvas.push_back(curve);

	// //TESTE
	this->notify(static_cast<void*>(line), Events::ADD_DRAWABLE);
}

void Canvas::addPolygon(const gchar *nome, std::vector<Vector> coords, bool fill){
	Drawable* pol = new Polygon(nome, coords, _window, fill);
	pol->setTipo("poligono");

	_canvas.push_back(pol);
	this->notify(pol, Events::ADD_DRAWABLE);
}

void Canvas::addCurve2(const gchar *nome, std::vector<Vector> points){
	Drawable* curve = new Curve2(nome, points, _window);
	curve->setTipo("curva");

	_canvas.push_back(curve);
	this->notify(curve, Events::ADD_DRAWABLE);
}

void Canvas::addPoint(const gchar *nome, Vector init_position){
	Point* p = new Point(nome, init_position, _window);
	p->setTipo("ponto");

	this->_canvas.push_back(static_cast<Drawable*>(p));
	this->notify(static_cast<void*>(p), Events::ADD_DRAWABLE);
}

void Canvas::drawCanvas(cairo_surface_t *surface)
{
	assert(surface);
	cairo_t *cr = cairo_create(surface);

	_window->draw(cr, _viewport);

	for(auto drawable: _canvas)
	{	
		drawable->draw(cr, _viewport);
	}
	cairo_stroke(cr);
}

void Canvas::updateWindow()
{
	for (auto drawable : _canvas)
	{
		drawable->updateWindow();
	}
}

void Canvas::deleteDrawable(const gchar* nome) {

	Drawable *ret = NULL;
	 for(size_t i = 0; i< this->_canvas.size(); i++){
	 	if(strcmp(_canvas.at(i)->getNome(),nome) == 0) {
			ret = _canvas[i];
	 		_canvas.erase(_canvas.begin()+i);
	 	}
	 }

	 notify(static_cast<void*>(ret), Events::REMOVE_DRAWABLE);
	delete ret;
}

void Canvas::translateDrawable(const gchar * name, Vector &offset)
{
	Drawable *ret = findDrawable(name);
	assert(ret);
	Transformation transformation = Transformation();
	transformation.translate(offset);

	ret->transform(transformation);

	notify(static_cast<void*>(ret), Events::TRANSFORMATION_TRANSLATE);
}

void Canvas::scaleDrawable(const gchar * name, Vector factor)
{
	Drawable *ret = findDrawable(name);
	Transformation transformation = Transformation();

	transformation.translate(-ret->getCenter()).scale(factor).translate(ret->getCenter());

	ret->transform(transformation);
	notify(static_cast<void*>(ret), Events::TRANSFORMATION_SCALE);
}

void Canvas::rotateDrawableOwnCenter(const gchar * name, float angle)
{
	Drawable *ret = findDrawable(name);
	Transformation transformation = Transformation();

	transformation.translate(ret->getCenter()).rotate(angle).translate(-ret->getCenter());

	ret->transform(transformation);
	notify(static_cast<void*>(ret), Events::TRANSFORMATION_ROTATE);
}

void Canvas::rotateDrawableSpecificCenter(const gchar * name, float angle, Vector center)
{
	Drawable *ret = findDrawable(name);
	Transformation transformation = Transformation();

	transformation.translate(center).rotate(angle).translate(-center);

	ret->transform(transformation);
	notify(static_cast<void*>(ret), Events::TRANSFORMATION_ROTATE);
}

void Canvas::rotateDrawableWorldCenter(const gchar * name, float angle)
{
	Drawable *ret = findDrawable(name);
	Transformation transformation = Transformation();

	transformation.rotate(angle);

	ret->transform(transformation);
	notify(static_cast<void*>(ret), Events::TRANSFORMATION_ROTATE);
}

void Canvas::onNotify(void * data, Events event)
{
	switch (event)
	{
	case WINDOW_MOVE:
	case WINDOW_ROTATE:
	case WINDOW_ZOOM:
		updateWindow();
		break;
	}
}

Drawable * Canvas::findDrawable(const gchar * name)
{
	for (size_t i = 0; i< this->_canvas.size(); i++) {
		if (strcmp(_canvas[i]->getNome(), name) == 0) {
			return _canvas[i];
		}
	}
	return nullptr;
}
