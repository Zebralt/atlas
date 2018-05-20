#include <iostream>

#include "label.hpp"

Label::Label(sf::Font* ft) : Widget() {
    name += "_label";
    label.setCharacterSize(20);
    textFont = ft;
    label.setFont(*textFont);
    label.setColor(sf::Color::Yellow);
    
    computeTextSize();
    alignText();
}

Label::Label() : Widget() {
    name += "_label";
    label.setCharacterSize(20);
    label.setColor(sf::Color::Yellow);
    
    computeTextSize();
    alignText();
}

Label::Label(std::string text, sf::Font* ft) : Widget() {
    name += "_label";

    this->label.setString(text);
    label.setCharacterSize(20);
    textFont = ft;
    label.setFont(*textFont);
    label.setColor(sf::Color::Yellow);
    
    computeTextSize();
    alignText();
}

void Label::setPosition(sf::Vector2f v) {
    position = origin+v;
    background.setPosition(position);
    label.setPosition(position+sf::Vector2f(0,label.getGlobalBounds().height/2));
    alignText();
}

void Label::setOrigin(sf::Vector2f v) {
//    position = position - origin + v;
//    background.setPosition(position);
//    origin = v;
	Widget::setOrigin(v);
    label.setPosition(position+sf::Vector2f(0,label.getGlobalBounds().height/2));
    alignText();
}

void Label::setText(std::string s) {
    label.setString(s);
    computeTextSize();
    alignText();
}

void Label::setTextColor(sf::Color c) {
    label.setColor(c);
}

void Label::setTextSize(int s) {
    label.setCharacterSize(s);
    computeTextSize();
    alignText();
}

void Label::setTextAlign(TextAlign a) {
    align = a;
    alignText();
}

void Label::setFont(sf::Font* f) {
    textFont = f;
    label.setFont(*f);
}

void Label::alignText() {
    sf::Vector2f tmp;
    switch(align) {
    case TextAlign::Left:
        tmp = position+sf::Vector2f(padding,(height - border_thickness*2)/2-label.getLocalBounds().height/2-label.getCharacterSize()/4);
    break;
    default:
    case TextAlign::Center:
        tmp = position+sf::Vector2f(width/2-label.getLocalBounds().width/2,(height - border_thickness*2)/2-label.getLocalBounds().height/2-label.getCharacterSize()/4);
    break;
    case TextAlign::Right:
        tmp = position+sf::Vector2f(-padding + width-label.getLocalBounds().width,(height - border_thickness*2)/2-label.getLocalBounds().height/2-label.getCharacterSize()/4);
    break;
    }
    tmp.x = roundf(tmp.x);
    tmp.y = roundf(tmp.y);
    label.setPosition(tmp);
}

void Label::computeTextSize() {
    setSize(label.getLocalBounds().width, label.getLocalBounds().height);
}

void Label::setOpacity(int r) {
    Widget::setOpacity(r);
    label.setColor(sf::Color(label.getColor().r,label.getColor().g,label.getColor().b,opacity));
}

sf::Text& Label::getText() {
    return label;
}

