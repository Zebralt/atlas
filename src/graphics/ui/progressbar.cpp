#include <SFML/Graphics.hpp>

#include "progressbar.hpp"
#include "../animation.hpp"
#include "../animations/progress_bar_animation.hpp"

ProgressBar::ProgressBar() : Widget() {
    value = 100;
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1);
    foreground.setFillColor(sf::Color::White);
}

void ProgressBar::goToValue(float t) {
//    ProgressBarAnimation* pba = new ProgressBarAnimation(this,t,30);
//    animate(pba,AnimationType::Value);
}

void ProgressBar::setValue(float t) {
    value = t;
    foreground.setSize(sf::Vector2f(width*value/100,foreground.getSize().y));
}

void ProgressBar::setSize(int w, int h) {
    width = w;
    height = h;
    background.setSize(sf::Vector2f(w,h));
    foreground.setSize(sf::Vector2f(w-4,h-4));
}

void ProgressBar::setColor(sf::Color c) {
    foreground.setFillColor(sf::Color(c.r,c.g,c.b,opacity));
}

//bool ProgressBar::animated() {
//    return animations.size();
//}

void ProgressBar::setPosition(sf::Vector2f v) {
    position = origin + v;
    background.setPosition(position);
    foreground.setPosition(position+sf::Vector2f(2,2));
}

void ProgressBar::setOrigin(sf::Vector2f v) {
    position = position-origin+v;
    background.setPosition(position);
    foreground.setPosition(position+sf::Vector2f(2,2));
    origin = v;
}

void ProgressBar::onMouseOverIn() {

}

void ProgressBar::onMouseOverOut() {

}

void ProgressBar::setOpacity(int r) {
    opacity = r;
    if (opacity > 255) opacity = 255;
    else if (opacity < 0) opacity = 0;
    background.setFillColor(sf::Color(background.getFillColor().r,background.getFillColor().g,background.getFillColor().b,r));
    foreground.setFillColor(sf::Color(foreground.getFillColor().r,foreground.getFillColor().g,foreground.getFillColor().b,r));

}

float ProgressBar::getValue() {
    return value;
}
