#include "../global.hpp"
#include "graphic_obj.hpp"

Blob::Blob() : Drawable(), Temporary(), Object() {
    this->origin = sf::Vector2f(0,0);
    this->position = sf::Vector2f(0,0);
    width = 20;
    height = 20;
    background.setSize(sf::Vector2f(width,height));
    background.setFillColor(sf::Color::Transparent);

    //backgroundImage = NULL;
    //gui.addWidget(*this);
}

void Blob::runAnimation(Action* a) {
    if (a) {
        if (a->type() != None) {
            if (typed_animations.find(a->type()) != typed_animations.end()) {
                _FREE(typed_animations[a->type()]);
            }
            typed_animations[a->type()] = a;
        }
        else {
            generic_animations.push_back(a);
        }
        a->set_target(this);
    }
}

void Blob::update() {
    
    if (status != IDLE) {
        update_or_delete(typed_animations);
        update_or_delete(generic_animations);
    }
    
}

bool Blob::terminated() {
//    if (!status && animations.size()) LOG("booyah ! widget is dead but still animated");
    return status == TERMINATED && !animated();
}

bool Blob::animated() {
    return generic_animations.size() || typed_animations.size();
}

Blob::~Blob() {
    for (auto it = typed_animations.begin(); it != typed_animations.end(); ++it) {
        _FREE(it->second);
    }
    
    for (auto& ptr : generic_animations) {
        _FREE(ptr);
    }
}

/*
void Blob::setName(std::string s) {
    name = s;
}*/
/*

std::string Blob::getName() {
    return name;
}
*/
/*
void Blob::setBackgroundImage(Picture& p) {
    this->backgroundImage = &p;
    width = p.getSize().w;
    height = p.getSize().h;
    p.setPosition(sf::Vector2f(0,0));
    p.setOpacity(opacity);
    p.setOrigin(position);
}
*/
/*
bool Blob::isOver(sf::Vector2f v) {
    return
    (v.x >= position.x && v.x <= position.x + width &&
    v.y  >= position.y && v.y <= position.y + height);
}
*/
