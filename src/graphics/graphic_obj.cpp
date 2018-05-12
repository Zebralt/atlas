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

void Blob::animate(Animation* a, AnimationType type) {
    if (animations.find(type) != animations.end()) {
        delete(animations[type]);
        //animations.erase(type);
    }
    animations[type] = a;
}

void Blob::update() {
    for (std::map<AnimationType, Animation*>::const_iterator it = animations.begin(); it != animations.end(); ++it) {
        it->second->update();
        if (it->second->getStatus() == TERMINATED) {
            delete(it->second);
            it = animations.erase(it); 
//            std::cout << "animation ended : now " << animations.size() << std::endl;
            if (!animations.size()) break;
            it--;
        }
        else {
            //LOG("animation ongoing");
        }
    }
    
}

bool Blob::isDead() {
//    if (!status && animations.size()) LOG("booyah ! widget is dead but still animated");
    return status == TERMINATED && !animations.size();
}

bool Blob::isAnimated() {
    return animations.size();
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
