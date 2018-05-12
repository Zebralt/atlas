/*#include <iostream>

#include "button.hpp"
#include "gui.hpp"

Button::Button(GraphicalUserInterface& gui) : GraphicObj(gui) {

    label.setCharacterSize(20);
    textFont = gui.getGlobalFont();
    label.setFont(textFont);
    label.setColor(sf::Color::Yellow);
    align = zegui::TextAlign::Center;
    alignText();
}

void Button::setPosition(sf::Vector2f v) {
    position = origin+v;
    background.setPosition(position);
    label.setPosition(position);
    alignText();
}

void Button::setOrigin(sf::Vector2f v) {
    position = position - origin + v;
    background.setPosition(position);
    label.setPosition(position);
    origin = v;
    alignText();
}

void Button::setText(std::string s) {
    label.setString(s);
    alignText();
}

void Button::setTextColor(sf::Color c) {
    label.setColor(c);
}

void Button::setTextSize(int s) {
    label.setCharacterSize(s);
    alignText();
}

void Button::setTextAlign(TextAlign a) {
    align = a;
    alignText();
}

void Button::alignText() {
    sf::Vector2f tmp;
    switch(align) {
    case zegui::TextAlign::Left:
        tmp = position+sf::Vector2f(0,height/2-label.getLocalBounds().height/2-label.getCharacterSize()/2);
    break;
    default:
    case zegui::TextAlign::Center:
        tmp = position+sf::Vector2f(width/2-label.getLocalBounds().width/2,height/2-label.getLocalBounds().height/2-label.getCharacterSize()/2);
    break;
    case zegui::TextAlign::Right:
        tmp = position+sf::Vector2f(width-label.getLocalBounds().width,height/2-label.getLocalBounds().height/2-label.getCharacterSize()/2);
    break;
    }
    tmp.x = roundf(tmp.x);
    tmp.y = roundf(tmp.y);
    label.setPosition(tmp);
}

//    void Button::onMouseOverIn() {
//		//setBackgroundColor(sf::Color(255,255,0,opacity));
//		FadeOut* f = new FadeOut(this,10,255);
//		animate(f,AnimationType::Fading);
//	}
//
//	void Button::onMouseOverOut() {
//		//setBackgroundColor(sf::Color(255,255,255,opacity));
//		FadeIn* f = new FadeIn(this,10,100);
//		animate(f,AnimationType::Fading);
//	}

void Button::onClick() {

}

void Button::setOpacity(int r) {
    opacity = r;
    if (opacity > 255) opacity = 255;
    else if (opacity < 0) opacity = 0;
    background.setFillColor(sf::Color(background.getFillColor().r,background.getFillColor().g,background.getFillColor().b,opacity));
    label.setColor(sf::Color(label.getColor().r,label.getColor().g,label.getColor().b,opacity));
}


bool Button::isAnimated() {
    return animations.size();
}

*/
