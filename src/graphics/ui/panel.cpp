#include <iostream>

#include "panel.hpp"
#include "../../engine/engine.hpp"

Panel::Panel() : Widget() {

}

void Panel::setPosition(sf::Vector2f v) {
    position = origin+v;
    background.setPosition(position);
    for (uint i=0;i<items.size();i++) {
        if (items[i]) items[i]->setOrigin(position);
    }
    if (layout) layout->layoutTarget();
}

void Panel::setOrigin(sf::Vector2f v) {
//    position = position - origin + v;
//    background.setPosition(position);
//    origin = v;
	Widget::setOrigin(v);
    for (uint i=0;i<items.size();i++) {
        items[i]->setOrigin(position);
    }
    if (layout) layout->layoutTarget();
}

void Panel::add(Widget* w) {
    Container::add(w);
    w->setOrigin(position);
    if (layout) layout->layoutTarget();
}

Widget* Panel::getItem(std::string name) {
    for (uint i=0;i<items.size();i++) {
        if (items[i] && items[i]->getName() == name) {
            return items[i];
        }
    }
    return nullptr;
}

void Panel::setOpacity(int r) {
    Widget::setOpacity(r);
//    LOG("panel::setopacity(" << r << ")");
    for (uint i=0;i<items.size();i++) {
        items[i]->setOpacity(opacity);
    }
}

void Panel::setSize(int w, int h) {
    Widget::setSize(w,h);
    if (layout) layout->layoutTarget();
}

void Panel::setStatus(short s) {
    Widget::setStatus(s);
    if (s == TERMINATED)
    for (uint i=0;i<items.size();i++) {
        items[i]->setStatus(IDLE);
    }
}

void Panel::update() {
    Widget::update();
    /*for (uint i=0;i<items.size();i++) {
        if (items[i]) items[i]->update();
        else LOG("null item in panel<" << name << ">");
    }*/
}

void Panel::move_in(Engine* app) {
//	if (background_image) {
//		app->add_widget(background_image->getName(), background_image);
//	}
//    for (uint i=0;i<items.size();i++) {
//        if (items[i]) app->add_widget(items[i]->getName(),items[i]);
//        else LOG("null item in panel<" << name << ">");
//    }
}

void Panel::move_out(Engine* app) {
//	if (background_image) app->remove_widget(background_image->getName());
//    for (uint i=0;i<items.size();i++) {
//        if (items[i]) app->remove_widget(items[i]->getName());
//        else LOG("null item in panel<" <<  name << ">");
//    }
}

void Panel::setLayout(Layout* l) {
    if (layout) {
        Layout* e = layout;
        delete(e);
    }
    layout = l;
    layout->layoutTarget();
}

/////////////////////////////////////////////////////////////////////////////////

void ColumnLayout::layoutTarget() {
    uint tmp_size = target->size();
    for (uint i=0;i<tmp_size; i++) {
        Widget* w = (*target)[i];
        if (w) {
            if (margin) {
                float true_global_height = target->getSize().h - margin * (tmp_size + 1);
                float true_element_height = true_global_height/tmp_size;
                float remainder = true_element_height - (long) true_element_height;
                LOG("remainder=" << remainder);
                if (remainder) {
                    /// resize time !
                    true_element_height += (1 - remainder);
                    float new_width = target->getSize().w;
                    float new_height = true_element_height*tmp_size+margin*(1+tmp_size);
                    LOG(target->getSize().h << "->" << new_height);
                    target->Widget::setSize(new_width, new_height);
                }
            }
            {
                w->setSize(target->getSize().w - margin*2, target->getSize().h/tmp_size);
                w->setPosition(sf::Vector2f(0,w->getSize().h*i));
//                w->setBackgroundColor(sf::Color(10*i+50,20*i,15*i));
            }
        }
    }
}

//elem:size = w - margin - margin, 	(h - margin*(elems + 1))/elems
//elem:pos  = margin,			margin + i*elems:size:h + margin*(i-1)	

void GridLayout::layoutTarget() {
    uint row_it = 0;
    uint col_it = 0;
    uint tmp_size = target->size();
    for (uint i=0;i<tmp_size;i++) {
        Widget* w = (*target)[i];
        if (w) {
            /*if (margin) {
                float true_global_height = target->getSize().h - margin * (tmp_size + 1);
                float true_element_height = true_global_height/tmp_size;
                float remainder = true_element_height - (long) true_element_height;
                LOG("remainder=" << remainder);
                if (remainder) {
                    /// resize time !
                    true_element_height += (1 - remainder);
                    float new_width = target->getSize().w;
                    float new_height = true_element_height*tmp_size+margin*(1+tmp_size);
                    LOG(target->getSize().h << "->" << new_height);
                    target->Widget::setSize(new_width, new_height);
                }
            }*/
            {
                w->setSize(target->getSize().w/cols-margin*(2+cols), target->getSize().h/rows-margin*(2+rows));
                w->setPosition(sf::Vector2f(margin+w->getSize().w*col_it+col_it*margin,margin+w->getSize().h*row_it+row_it*margin));
                //w->setBackgroundColor(sf::Color(10*i+50,20*i,15*i));
            }
        }
        
        // special iterators
        if (orientation) {
            col_it++;
            if (col_it >= cols) {
                col_it = 0;
                row_it++;
                if (row_it >= rows) {
                    break;
                }
            }
        }
        else {
            row_it++;
            if (row_it >= cols) {
                row_it = 0;
                col_it++;
                if (col_it >= rows) {
                    break;
                }
            }
        }
        
    }
}

/// PANEL BACKGROUND IMAGE

void Panel::setBackgroundImage(PictureBox* image) {
	if (image) {
		background_image = image;
		background_image->setOrigin(position);
//		setOrigin(position);
		adjustBackgroundImage();
	}
}

void Panel::setBackgroundImageSize(int w, int h) {
	if (background_image) {
		background_image->setSize(w,h);
		adjustBackgroundImage();
	}
}

void Panel::fitBackgroundImage(float fx, float fy) {
	if (background_image) {
		background_image->setSize(width*fx,height*fy);
		adjustBackgroundImage();
	}
}

void Panel::fitBackgroundImage(float factor = 1) {
	if (background_image) {
		background_image->setSize(width*factor,height*factor);
		adjustBackgroundImage();
	}
}

void Panel::adjustBackgroundImage() {
	if (background_image) {
		background_image->setPosition(sf::Vector2f(width/2 - background_image->getSize().w/2,height/2 - background_image->getSize().h/2));
	}
}

Panel::~Panel() {
//	if (background_image) delete(background_image);
	if (layout) delete(layout);
}