#include <iostream>

#include "panel.hpp"
#include "engine/engine.hpp"

// namespace atlas_engine {
//namespace Graphics {
//namespace gui {

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

//void Panel::move_in(Engine* app) {
////	if (background_image) {
////		app->add_widget(background_image->getName(), background_image);
////	}
////    for (uint i=0;i<items.size();i++) {
////        if (items[i]) app->add_widget(items[i]->getName(),items[i]);
////        else LOG("null item in panel<" << name << ">");
////    }
//}
//
//void Panel::move_out(Engine* app) {
////	if (background_image) app->remove_widget(background_image->getName());
////    for (uint i=0;i<items.size();i++) {
////        if (items[i]) app->remove_widget(items[i]->getName());
////        else LOG("null item in panel<" <<  name << ">");
////    }
//}

void Panel::register_elements() {
    for (auto item : items) {
        Engine::register_widget(item);
    }
}

void Panel::setLayout(Layout* l) {
    if (!l) return;
    if (layout) {
        Layout* e = layout;
        delete(e);
    }
    layout = l;
    layout->setTarget(this);
    if (size()) layout->layoutTarget();
}

/// PANEL BACKGROUND IMAGE
//
//void Panel::setBackgroundImage(PictureBox* image) {
//	if (image) {
//		background_image = image;
//		background_image->setOrigin(position);
////		setOrigin(position);
//		adjustBackgroundImage();
//	}
//}
//
//void Panel::setBackgroundImageSize(int w, int h) {
//	if (background_image) {
//		background_image->setSize(w,h);
//		adjustBackgroundImage();
//	}
//}
//
//void Panel::fitBackgroundImage(float fx, float fy) {
//	if (background_image) {
//		background_image->setSize(width*fx,height*fy);
//		adjustBackgroundImage();
//	}
//}
//
//void Panel::fitBackgroundImage(float factor = 1) {
//	if (background_image) {
//		background_image->setSize(width*factor,height*factor);
//		adjustBackgroundImage();
//	}
//}
//
//void Panel::adjustBackgroundImage() {
//	if (background_image) {
//		background_image->setPosition(sf::Vector2f(width/2 - background_image->getSize().w/2,height/2 - background_image->getSize().h/2));
//	}
//}

Panel::~Panel() {
//	if (background_image) delete(background_image);
	if (layout) delete(layout);
	for (auto item : items) {
        item->setStatus(TERMINATED);
	}
}

//}
//}
// } // namespace