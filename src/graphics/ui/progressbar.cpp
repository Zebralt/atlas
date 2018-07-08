#include <SFML/Graphics.hpp>

#include "progressbar.hpp"
#include "graphics/animation.hpp"
#include "graphics/animations/progress_bar_animation.hpp"

// namespace atlas_engine {
//namespace Graphics {
//namespace gui {
    
ProgressBar::ProgressBar(ProgressBarStyle p) : Widget() {
    value = 100;
    setStyle(p);
    
    background.setFillColor(sf::Color(30, 30, 30));
    background.setOutlineColor(sf::Color::White);
//    background.setOutlineThickness(1);
    foreground.setFillColor(sf::Color(120, 120, 150));
    setValue(50);
    setPadding(0);
    clear_actions();

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
    foreground.setSize(sf::Vector2f(w*value/100-padding*2,h-padding*2));
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
    foreground.setPosition(position+sf::Vector2f(padding, padding));
}

void ProgressBar::setOrigin(sf::Vector2f v) {
    position = position-origin+v;
    background.setPosition(position);
    foreground.setPosition(position+sf::Vector2f(padding, padding));
    origin = v;
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

void ProgressBar::setStyle(ProgressBarStyle p) {
    switch(p) {
        case ProgressBarStyle::Cursor:
            
            break;
        case ProgressBarStyle::Caret:
        
        default:break;
    }
}

void ProgressBar::setCursorSize(int w, int h) {
    
}

//}
//}
// } // namespace Video::gui