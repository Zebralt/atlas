#include "picture_box.hpp"


PictureBox::PictureBox() : Widget() {

}

PictureBox::PictureBox(std::string s) : Widget() {
	picture = new Picture(s);
}

PictureBox::PictureBox(sf::Texture* t) : Widget() {
	picture = new Picture(t);
}

PictureBox::PictureBox(Picture* p) : Widget() {
	picture = p;
	width = p->getSize().w;
	height = p->getSize().h;
}

PictureBox::PictureBox(sf::Color c) : Widget() {
	setBackgroundColor(c);
}

void PictureBox::update() {
	Widget::update();
	if (picture) picture->update();
}

void PictureBox::setPosition(sf::Vector2f v) {
	Widget::setPosition(v);
	if (picture) picture->setPosition(v);
}

void PictureBox::setOrigin(sf::Vector2f v) {
	Widget::setOrigin(v);
	if (picture) picture->setOrigin(v);
}

void PictureBox::setOpacity(int r) {
	Widget::setOpacity(r);
	if (picture) picture->setOpacity(r);
}

void PictureBox::setSize(int w,int h) {
	Widget::setSize(w,h);
	if (picture) picture->setSize(w,h);
}

PictureBox::~PictureBox() {
	delete(picture);
}

void PictureBox::draw(sf::RenderTarget& tar, sf::RenderStates stt) const {
	Widget::draw(tar,stt);
	if (picture) tar.draw(*picture);
}