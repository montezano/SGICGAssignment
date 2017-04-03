#include "ControllerMainWindow.h"

ControllerMainWindow::ControllerMainWindow(GtkBuilder * builder, const Controller *controller, Canvas *canvas, Viewport *viewport, Windowport *windowport)
{
	assert(windowport);
	_windowport = windowport;
	assert(viewport);
	_viewport = viewport;
	_window = new MainWindow(GTK_WIDGET(gtk_builder_get_object(builder, "main_window")));
	assert(_window);

	_window_coordinates = new WindowCoordinates(GTK_WIDGET(gtk_builder_get_object(builder, "window_coordinates")));
	assert(_window_coordinates);

	assert(controller);
	_controller = controller;

	configureButtons(builder);

	g_signal_connect(_window->getDrawingArea(), "configure-event", G_CALLBACK(configure_event_cb), NULL);
	g_signal_connect(_window->getDrawingArea(), "draw", G_CALLBACK(draw_cb), NULL);

	_treeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "object_list_treeview"));

	_canvas = canvas;
}

ControllerMainWindow::~ControllerMainWindow()
{
}

void ControllerMainWindow::display()
{
	_window->display();
}

void ControllerMainWindow::initialize()
{
}

Window * ControllerMainWindow::getWindow()
{
	return _window;
}

void ControllerMainWindow::configureButtons(GtkBuilder *builder)
{
	GtkButton* button;
	GtkToolButton* toolButton;

	/////////////////////////////////
	/// ADD/REMOVE BUTTONS
	/////////////////////////////////
	_radio_button_linha = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_add_line"));

	_radio_button_poligono = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_add_polygon"));

	_radio_button_ponto = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_add_point"));

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_add_object"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(add_object_cb), NULL);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_remove_object"));
	g_signal_connect(toolButton, "clicked", G_CALLBACK(remove_object), NULL);

	/////////////////////////////////
	/// WINDOW BUTTONS
	/////////////////////////////////
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_cima"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(move_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_baixo"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(move_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_esquerda"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(move_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_direita"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(move_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_zoom_in"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(zoom_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_zoom_out"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(zoom_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_rotation_right"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(rotate_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_rotation_left"));
	g_signal_connect_swapped(toolButton, "clicked", G_CALLBACK(rotate_cb), toolButton);

	/////////////////////////////////
	/// TRANSOFRMATION BUTTONS
	/////////////////////////////////
	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_up"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(translate_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_left"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(translate_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_down"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(translate_cb), toolButton);

	toolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "button_translation_right"));
	assert(toolButton);	g_signal_connect(toolButton, "clicked", G_CALLBACK(translate_cb), toolButton);

	GtkScale *_scale;
	_scale = GTK_SCALE(gtk_builder_get_object(builder, "scale_rotation_x"));
	g_signal_connect(_scale, "button-release-event", G_CALLBACK(rotate_object_cb), NULL);

	_scale = GTK_SCALE(gtk_builder_get_object(builder, "scale_rotation_y"));
	gtk_widget_hide(GTK_WIDGET(_scale));

	_radio_button_rotation_world = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_rotation_center"));
	_radio_button_rotation_self = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_rotation_object"));
	_radio_button_rotation_specific = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "radiobutton_rotation_other"));
	g_signal_connect(_radio_button_rotation_specific, "clicked", G_CALLBACK(rotate_specific_cb), NULL);

	_scale = GTK_SCALE(gtk_builder_get_object(builder, "scale_scaling"));
	g_signal_connect(_scale, "button-release-event", G_CALLBACK(scale_cb), NULL);

	/////////////////////////////////
	/// COORDINATES WINDOW
	/////////////////////////////////
	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_coordinates_ok"));
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window_coordinates->getWindow());

	button = GTK_BUTTON(gtk_builder_get_object(builder, "button_coordinates_cancel"));
	g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_hide), _window_coordinates->getWindow());

	g_signal_connect(_window_coordinates->getWindow(), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	/////////////////////////////////
	/// CLIPPING ALGORITHM SELECTION
	/////////////////////////////////
	GtkRadioMenuItem *item;

	item = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(builder, "radiomenu_point"));
	assert(item);
	g_signal_connect(item, "toggled", G_CALLBACK(point_algorithm_cb), NULL);

	item = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(builder, "radiomenu_linecs"));
	assert(item);
	g_signal_connect(item, "toggled", G_CALLBACK(line_algorithm_cb), NULL);

	item = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(builder, "radiomenu_linelb"));
	assert(item);
	g_signal_connect(item, "toggled", G_CALLBACK(line_algorithm_cb), NULL);

	item = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(builder, "radiomenu_linenicholl"));
	assert(item);
	g_signal_connect(item, "toggled", G_CALLBACK(line_algorithm_cb), NULL);

	item = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(builder, "radiomenu_polsuthodg"));
	assert(item);
	g_signal_connect(item, "toggled", G_CALLBACK(polygon_algorithm_cb), NULL);

	item = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(builder, "radiomenu_polweil"));
	assert(item);
	g_signal_connect(item, "toggled", G_CALLBACK(polygon_algorithm_cb), NULL);
}





///////////////////////////////////////////////////////////////////////
//	CALLBACK FUNCTIONS
///////////////////////////////////////////////////////////////////////
void ControllerMainWindow::move_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	std::string button_name = gtk_tool_button_get_label(GTK_TOOL_BUTTON(widget));

	if (button_name == "Cima")
	{
		_windowport->move(Vector(0,10.f));
	}
	else
	{
		if (button_name == "Direita")
		{
			_windowport->move(Vector(10.f , 0));
		}
		else
		{
			if (button_name == "Baixo")
			{
				_windowport->move(Vector(0, -10.f));
			}
			else
			{
				if (button_name == "Esquerda")
				{
					_windowport->move(Vector(-10.f, 0));
				}
				else
				{
					assert(false);
				}
			}
		}
	}
}

void ControllerMainWindow::zoom_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	std::string button_name = gtk_tool_button_get_label(GTK_TOOL_BUTTON(widget));
	if (button_name == "Amplia")
	{
		_windowport->zoom(1.2f);
	}
	else
	{
		if (button_name == "Reduzir")
		{
			_windowport->zoom(0.8f);
		}
		else
		{
			assert(false);
		}
	}
}

void ControllerMainWindow::rotate_cb(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
	std::string button_name = gtk_tool_button_get_label(GTK_TOOL_BUTTON(widget));
	if (button_name == "Rotaciona direita")
	{
		_windowport->rotate(10.f);
	}
	else
	{
		if (button_name == "Rotaciona esquerda")
		{
			_windowport->rotate(-10.f);
		}
		else
		{
			assert(false);
		}
	}
}

void ControllerMainWindow::translate_cb(GtkWidget *widget)
{
	Vector factor = Vector(0,0);
	std::string button_name = gtk_tool_button_get_label(GTK_TOOL_BUTTON(widget));
	const char *drawable_name = getObjectSelected();
	if (drawable_name)
	{
		if (button_name == "Cima")
		{
			factor.y = 10;
			_canvas->translateDrawable(drawable_name, factor);
		}
		else
		{
			if (button_name == "Direita")
			{
				factor.x = 10;
				_canvas->translateDrawable(drawable_name, factor);
			}
			else
			{
				if (button_name == "Baixo")
				{
					factor.y = -10;
					_canvas->translateDrawable(drawable_name, factor);
				}
				else
				{
					if (button_name == "Esquerda")
					{
						factor.x = -10;
						_canvas->translateDrawable(drawable_name, factor);
					}
					else
					{
						assert(false);
					}
				}

			}
		}
	}

}

void ControllerMainWindow::point_algorithm_cb(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
}

void ControllerMainWindow::line_algorithm_cb(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{

	GSList *toggle_button = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(widget));
	//int index = -1;
	if (toggle_button)
	{
		do
		{
			if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(toggle_button->data)))
			{
				break;
			}
		} while ((toggle_button = g_slist_next(toggle_button)) != NULL);
	}

	std::string button_name = gtk_menu_item_get_label(GTK_MENU_ITEM(toggle_button->data));

	if (button_name == "Cohen Sutherland")
	{
	}
	else
	{
		if (button_name == "Liang-Barsky")
		{
		}
		else
		{
		}
	}
}

void ControllerMainWindow::polygon_algorithm_cb(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
	GSList *toggle_button = gtk_radio_menu_item_get_group(_radio_menu_line);
	//int index = -1;
	if (toggle_button)
	{
		do
		{
			if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(toggle_button->data)))
			{
				break;
			}
		} while ((toggle_button = g_slist_next(toggle_button)) != NULL);
	}


	std::string button_name = gtk_menu_item_get_label(GTK_MENU_ITEM(toggle_button->data));

	if (button_name == "Sutherland Hodgeman")
	{
	}
	else
	{
		if (button_name == "Weiler Atherton")
		{
		}
	}
}

gboolean ControllerMainWindow::rotate_object_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	const gchar *nome = getObjectSelected();
	if (nome)
	{
		GSList *toggle_button = gtk_radio_button_get_group(_radio_button_rotation_world);
		//int index = -1;
		if (toggle_button)
		{
			do
			{
				if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button->data)))
				{
					break;
				}
			} while ((toggle_button = g_slist_next(toggle_button)) != NULL);
		}

		GtkButton *button = GTK_BUTTON(toggle_button->data);
		std::string button_name = gtk_button_get_label(button);

		if (button_name == "Centro")
		{
			_canvas->rotateDrawableWorldCenter(nome, static_cast<float>(gtk_range_get_value(GTK_RANGE(widget))));
		}
		else
		{
			if (button_name == "Objeto")
			{
				_canvas->rotateDrawableOwnCenter(nome, static_cast<float>(gtk_range_get_value(GTK_RANGE(widget))));
			}
			else
			{
				_canvas->rotateDrawableSpecificCenter(nome, static_cast<float>(gtk_range_get_value(GTK_RANGE(widget))), _window_coordinates->getCoordinates());
			}
		}
	}
	return FALSE;
}

void ControllerMainWindow::rotate_specific_cb()
{
	_window_coordinates->display();
}

gboolean ControllerMainWindow::scale_cb(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
	const gchar *nome = getObjectSelected();
	if (nome)
	{
		_canvas->scaleDrawable(nome,
			Vector(static_cast<float>(gtk_range_get_value(GTK_RANGE(widget))),
					static_cast<float>(gtk_range_get_value(GTK_RANGE(widget)))));
	}
	return FALSE;

}

void ControllerMainWindow::remove_object()
{
	const char *name = getObjectSelected();
	if (name)
	{
		_canvas->deleteDrawable(name);

		gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
	}
}

void ControllerMainWindow::add_object_cb()
{
	GSList *toggle_button = gtk_radio_button_get_group(_radio_button_linha);
	int index = -1;
	if (toggle_button)
	{
		do
		{
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(toggle_button->data)))
			{
				break;
			}
		} while ((toggle_button = g_slist_next(toggle_button)) != NULL);
	}

	GtkButton *button = GTK_BUTTON(toggle_button->data);
	std::string button_name = gtk_button_get_label(button);

	if(button_name == "Linha")
	{
		_controller->_window_linha_controller->display();
	}
	else
	{
		if (button_name == "Poligono")
		{
			_controller->_window_poligono_controller->display();
		}
		else
		{
			_controller->_window_ponto_controller->display();
		}
	}
}

gboolean ControllerMainWindow::draw_cb(GtkWidget * widget, cairo_t * cr, gpointer data)
{
	_canvas->drawCanvas(_window->getSurface());
	return _window->draw_window(widget, cr, data);
}

gboolean ControllerMainWindow::configure_event_cb(GtkWidget * widget, GdkEventConfigure * event, gpointer data)
{
	gboolean ret = _window->configure_event(widget, event, data);
	return ret;
}

const gchar * ControllerMainWindow::getObjectSelected()
{

	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(_treeView));
	if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
		const gchar *name;
		gtk_tree_model_get(model, &iter, 0, &name, -1);
		return name;

	}
	else {
		g_print("no row selected.\n");
		return nullptr;
	}
}

MainWindow *ControllerMainWindow::_window = NULL;
WindowCoordinates *ControllerMainWindow::_window_coordinates = NULL;
const Controller *ControllerMainWindow::_controller = NULL;
Viewport *ControllerMainWindow::_viewport = NULL;
Canvas *ControllerMainWindow::_canvas = NULL;
GtkTreeView* ControllerMainWindow::_treeView = NULL;
Windowport *ControllerMainWindow::_windowport = NULL;


GtkRadioButton *ControllerMainWindow::_radio_button_linha = NULL;
GtkRadioButton *ControllerMainWindow::_radio_button_poligono = NULL;
GtkRadioButton *ControllerMainWindow::_radio_button_ponto = NULL;

GtkRadioButton *ControllerMainWindow::_radio_button_rotation_world = NULL;
GtkRadioButton *ControllerMainWindow::_radio_button_rotation_self = NULL;
GtkRadioButton *ControllerMainWindow::_radio_button_rotation_specific = NULL;

GtkRadioMenuItem *ControllerMainWindow::_radio_menu_line = NULL;
GtkRadioMenuItem *ControllerMainWindow::_radio_menu_polygon = NULL;

GtkTreeSelection *ControllerMainWindow::selection = NULL;
GtkTreeIter ControllerMainWindow::iter;
GtkTreeModel *ControllerMainWindow::model;

