#include "Canvas.h"

#include <assert.h>

Canvas::Canvas(Viewport *viewport)
{
	_viewport = viewport;
}

Canvas::Canvas()
{
}


Canvas::~Canvas()
{

}

void Canvas::addLine(const gchar* nome, Vector inicial, Vector fim)
{
	//this->notify(static_cast<void*>(d), Events::ADD_DRAWABLE);
	//_canvas.push_back(static_cast<Drawable*>(d));
	Drawable* line = new Line(nome,inicial,fim);
	line->setTipo("linha");
	
	_canvas.push_back(line);
	this->notify(static_cast<void*>(line), Events::ADD_DRAWABLE);
}

void Canvas::addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords){
	Drawable* pol = new Polygon(nome,init_position,coords);
	pol->setTipo("poligono");

	_canvas.push_back(pol);
	this->notify(pol, Events::ADD_DRAWABLE);
}

void Canvas::addPoint(const gchar *nome, Vector init_position){
	Point* p = new Point(nome, init_position);
	p->setTipo("ponto");

	this->_canvas.push_back(static_cast<Drawable*>(p));
	this->notify(static_cast<void*>(p), Events::ADD_DRAWABLE);
}

void Canvas::drawCanvas(cairo_surface_t *surface)
{
	assert(surface);
	cairo_t *cr = cairo_create(surface);

	for(auto drawable: _canvas)
	{
		drawable->draw(cr, _viewport);
	}
	cairo_stroke(cr);
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

	 notify(static_cast<void*>(ret), Events::REMOVE_DRAWABLE);
	delete ret;
}