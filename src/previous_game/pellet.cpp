#include "pellet.hpp"

Pellet::Pellet() : MobileObj() {

}

int random(int a, int b) {
	return rand()%(b-a)+a;
}

PelletView::PelletView(Pellet* p) : MobileObjView(p) {
	m_sprite.setColor(sf::Color(random(100,255),random(100,255),random(100,255)));
}