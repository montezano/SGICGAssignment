#include "model/Canvas.h"

#include <assert.h>

Canvas::Canvas(cairo_surface_t *surface)
{
	assert(_surface);
	_surface = surface;
}

Canvas::~Canvas()
{

}

void Canvas::addLine(const gchar* nome, Vector inicial, Vector fim)
{
	g_print("addDrawable\n");
	Line* line = new Line(nome,inicial,fim);
	line->setTipo("linha");
	_canvas.push_back(static_cast<Drawable*>(line));
}

void Canvas::addPolygon(const gchar *nome, Vector init_position, std::vector<Vector> coords){
	Polygon* pol = new Polygon(nome,init_position,coords);
	pol->setTipo("poligono");
	_canvas.push_back(static_cast<Drawable*>(pol));
}

void Canvas::addPoint(const gchar *nome, Vector init_position){
	Point* p = new Point(nome, init_position);
	p->setTipo("ponto");
	g_print("add point\n");
	g_print(p->getNome());
	this->_canvas.push_back(static_cast<Drawable*>(p));
	g_print("add point2\n");
	g_print("%d",_canvas.size());
	g_print(this->_canvas[0]->getNome());

}
void Canvas::drawCanvas()
{
	// g_print("era prater desenhado!!\n");
	assert(_surface);
	for(auto drawable: _canvas)
	{
		// g_print("no for\n");
		drawable->draw(_surface);
	}
}

void Canvas::deleteDrawable(const gchar* nome) {
	g_print("%d",this->_canvas.size());
	g_print(this->_canvas[0]->getNome());
	// for(size_t i = 0; i< this->_canvas.size(); i++){
	// 	g_print("NOMES\n");
	// 	if(strcmp(_canvas.at(i)->getNome(),nome) == 0) {
	// 		_canvas.erase(_canvas.begin()+i);
	// 	}
	// }
}
