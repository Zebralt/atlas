#include "../global.hpp"
#include "drawable.hpp"

void Drawable::draw(sf::RenderTarget& target, sf::RenderStates stt) const {
//    stt *= getTransform();
    target.draw(background);
}

void Drawable::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    background.setSize(sf::Vector2f(width,height));
}

Size Drawable::getSize() {
    return Size(width,height);
}

int Drawable::getOpacity() {
    return opacity;
}

sf::Vector2f Drawable::getPosition() {
    return position;
}

sf::Rect<int> Drawable::getRect() {
    sf::Rect<int> r = sf::Rect<int>(position.x, position.y, width, height);
    //LOG(r.top << ":" << r.left << ":" << r.width << ":" << r.height);
    return r;
}

void Drawable::setPosition(sf::Vector2f v) {
    position = origin+v;
    background.setPosition(position);
}

void Drawable::move(sf::Vector2f v) {
	setPosition(position + v);
}

void Drawable::setOrigin(sf::Vector2f v) {
    position = position - origin + v;
    origin = v;
    background.setPosition(position);
}

void Drawable::setOpacity(int r) {
    opacity = r;
    if (opacity > 255) opacity = 255;
    else if (opacity < 0) opacity = 0;
    if (background.getFillColor() != sf::Color::Transparent || background.getFillColor().a >= opacity) background.setFillColor(sf::Color(background.getFillColor().r,background.getFillColor().g,background.getFillColor().b,opacity));
    if (background.getOutlineColor() != sf::Color::Transparent ||background.getOutlineColor().a >= opacity) background.setOutlineColor(sf::Color(background.getOutlineColor().r,background.getOutlineColor().g,background.getOutlineColor().b,opacity));
}


void Drawable::setBorder(int t, sf::Color c) {
    border_thickness = t;
    background.setOutlineThickness(t);
    background.setOutlineColor(c);
}

void Drawable::setBackgroundColor(sf::Color c) {
    background.setFillColor(c);
}

void Drawable::adjustBackground() {
    background.setSize(sf::Vector2f(width,height));
}

//void Drawable::fitBackground(float factor) {
//
//}
