#include "Canvas.h"

#include <assert.h>

Canvas::Canvas(Viewport *viewport, Windowport *window)
{
	assert(viewport);
	assert(window);
	_viewport = viewport;
	_window = window;

	_guideline_z = new Line("Guideline Z", new Vector(0.f, 0.f, -5000.f), new Vector(0.f, 0.f, 5000.f), _window);
	_guideline_x = new Line("Guideline X", new Vector(-5000.f, 0.f, 0.f), new Vector(5000.f, 0.f, 0.f), _window);
	_guideline_y = new Line("Guideline Y", new Vector(0.f, -5000.f, 0.f), new Vector(0.f, 5000.f, 0.f), _window);
}

Canvas::Canvas()
{
}


Canvas::~Canvas()
{
	for (Drawable *it : _canvas)
	{
		delete (it);
	}
	_canvas.clear();

	//delete(_guideline_z);
	//delete(_guideline_x);
	//delete(_guideline_y);
}

void Canvas::setWindow(Windowport * window)
{
	assert(window);
	_window = window;
}

void Canvas::addLine(const gchar* nome, Vector *inicial, Vector *fim)
{
	Drawable* line = new Line(nome,inicial,fim, _window);

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

	// //TESTE
	 std::vector<Line*> lines;
	 lines.push_back(new Line("linha11", new Vector(0, 0, 0),		new Vector(100, 0, 0), _window));
	 lines.push_back(new Line("linha12", new Vector(100, 0, 0),		new Vector(100, 0, 100), _window));
	 lines.push_back(new Line("linha13", new Vector(100, 0, 100),	new Vector(0, 0, 100), _window));
	 lines.push_back(new Line("linha14", new Vector(0, 0, 100),		new Vector(0, 0, 0), _window));
	 lines.push_back(new Line("linha14", new Vector(0, 0, 0),		new Vector(0, 100, 0), _window));
	 lines.push_back(new Line("linha14", new Vector(0, 100, 0),		new Vector(100, 100, 0), _window));
	 lines.push_back(new Line("linha14", new Vector(100, 100, 0),	new Vector(100, 0, 0), _window));
	 lines.push_back(new Line("linha14", new Vector(0, 100, 0),		new Vector(0, 100, 100), _window));
	 lines.push_back(new Line("linha14", new Vector(0, 100, 100),	new Vector(100, 100, 100), _window));
	 lines.push_back(new Line("linha14", new Vector(100, 100, 100),	new Vector(100, 100, 0), _window));
	 lines.push_back(new Line("linha14", new Vector(100, 100, 100),	new Vector(100, 0, 100), _window));
	 lines.push_back(new Line("linha14", new Vector(0, 100, 100),	new Vector(0, 0, 100), _window));


	 Drawable* object3d = new Object3D(nome, lines, _window);
	 //curve->setTipo("curva");

	 _canvas.push_back(object3d);

	// //TESTE

	this->notify(static_cast<void*>(line), Events::ADD_DRAWABLE);
}

void Canvas::addPolygon(const gchar *nome, std::vector<Vector*> coords, bool fill){
	Drawable* pol = new Polygon(nome, coords, _window, fill);

	_canvas.push_back(pol);
	this->notify(pol, Events::ADD_DRAWABLE);
}

void Canvas::addCurve2(const gchar *nome, std::vector<Vector*> points, bool type){
	Drawable* curve = new Curve2(nome, points, _window,type);

	_canvas.push_back(curve);
	this->notify(curve, Events::ADD_DRAWABLE);
}

void Canvas::addPoint(const gchar *nome, Vector *init_position){
	Point* p = new Point(nome, init_position, _window);

	this->_canvas.push_back(static_cast<Drawable*>(p));
	this->notify(static_cast<void*>(p), Events::ADD_DRAWABLE);
}

void Canvas::drawCanvas(cairo_surface_t *surface)
{
	assert(surface);
	cairo_t *cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 255, 255, 0);

	_guideline_x->draw(cr, _viewport);
	_guideline_y->draw(cr, _viewport);
	_guideline_z->draw(cr, _viewport);

	cairo_stroke(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);


	_window->draw(cr, _viewport);

	for(auto drawable: _canvas)
	{
		drawable->draw(cr, _viewport);
	}
	cairo_stroke(cr);

	cairo_destroy(cr);
}

void Canvas::updateWindow()
{
	_guideline_x->updateWindow();
	_guideline_y->updateWindow();
	_guideline_z->updateWindow();
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

void Canvas::rotateDrawableOwnCenter(const gchar * name, Vector &angle)
{
	Drawable *ret = findDrawable(name);
	Transformation transformation = Transformation();


	transformation.translate(ret->getCenter()).rotate(angle).translate(-ret->getCenter());

	ret->transform(transformation);
	notify(static_cast<void*>(ret), Events::TRANSFORMATION_ROTATE);
}

void Canvas::rotateDrawableSpecificCenter(const gchar * name, Vector &angle, Vector center)
{
	Drawable *ret = findDrawable(name);
	Transformation transformation = Transformation();

	Vector plane_normal = _window->getNormal();
	Vector aux_plane_normal_x = Vector(plane_normal.x, 0.f, plane_normal.z);
	Vector aux_plane_normal_y = Vector(0.f, plane_normal.y, plane_normal.z);
	Vector rot_angle = Vector(0, 0, 0);
	
	rot_angle.x = aux_plane_normal_x.angleBetwenVectors(Vector(0, 0, 1));
	rot_angle.y = aux_plane_normal_y.angleBetwenVectors(Vector(0, 0, 1));

	Vector neg_rot_angle = -rot_angle;

	transformation.translate(center).rotate(rot_angle).rotate(angle).rotate(neg_rot_angle).translate(-center);

	ret->transform(transformation);
	notify(static_cast<void*>(ret), Events::TRANSFORMATION_ROTATE);
}

void Canvas::rotateDrawableWorldCenter(const gchar * name, Vector &angle)
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
