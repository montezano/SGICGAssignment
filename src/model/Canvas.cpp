#include "model/Canvas.h"

#include <assert.h>

Canvas::Canvas(Viewport *viewport)
{
	_viewport = viewport;
}

Canvas::Canvas(cairo_surface_t *surface)
{
	assert(_surface);
	_surface = surface;
	_cr = cairo_create(_surface);
}

void Canvas::setSurface(cairo_surface_t * surface)
{
	assert(_surface);
	_surface = surface;
	_cr = cairo_create(_surface);
}

Canvas::~Canvas()
{

}

void Canvas::addLine(const gchar* nome, Vector inicial, Vector fim)
{
	//this->notify(static_cast<void*>(d), Events::ADD_DRAWABLE);
	//_canvas.push_back(static_cast<Drawable*>(d));
	g_print("addDrawable\n");
	Drawable* line = new Line(nome,inicial,fim);
	line->setTipo("linha");
	this->notify(line, Events::ADD_DRAWABLE);
	_canvas.push_back(line);
}

void Canvas::addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords){
	Drawable* pol = new Polygon(nome,init_position,coords);
	pol->setTipo("poligono");
	this->notify(pol, Events::ADD_DRAWABLE);

	_canvas.push_back(pol);
}

void Canvas::addPoint(const gchar *nome, Vector init_position){
	Point* p = new Point(nome, init_position);
	p->setTipo("ponto");
	g_print("add point\n");
	g_print(p->getNome());
	this->notify(p, Events::ADD_DRAWABLE);

	this->_canvas.push_back(static_cast<Drawable*>(p));
	g_print("add point2\n");
	g_print("%d",_canvas.size());
	g_print(this->_canvas[0]->getNome());

}

void Canvas::drawCanvas(cairo_t *cr)
{
	assert(_surface);
	for(auto drawable: _canvas)
	{
		drawable->draw(_cr, _viewport);
	}
	cairo_stroke(_cr);
}

void Canvas::updateViewport()
{

}

void Canvas::deleteDrawable(const gchar* nome) {
	//g_print("%d\n",this->_canvas.size());
	//g_print("antes\n");
	Drawable *ret = NULL;
	//g_print(this->_canvas[0]->getNome());
	 for(size_t i = 0; i< this->_canvas.size(); i++){
	 	g_print("NOMES\n");
	 	if(strcmp(_canvas.at(i)->getNome(),nome) == 0) {
			g_print("removendo!!\n");
			ret = _canvas[i];
	 		_canvas.erase(_canvas.begin()+i);
	 	}
	 }
	 cairo_destroy(_cr);

	 notify(ret, Events::REMOVE_DRAWABLE);
	 _cr = cairo_create(_surface);
	 drawCanvas(_cr);
	delete ret;

	 g_print("%d", this->_canvas.size());

}
