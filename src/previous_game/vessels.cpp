#include "vessels.hpp"
#include "phases.hpp"

Vessel::Vessel() : MobileObj() {
}

void Vessel::update() {
	MobileObj::update();
	
	// update shoot patterns

	if (shoot_pattern) shoot_pattern->update();
}

void Vessel::setShootWave(ShootWave* st) {
	shoot_pattern = st;
	st->master = this;
}

VesselView::VesselView(Vessel* v) : MobileObjView(v) {
}

void VesselView::update() {
	MobileObjView::update();
}

////////////////////////////////////

PlayerVessel::PlayerVessel() : MobileObj() {
	speed = 2;
	orientation = 0;	
}

void PlayerVessel::update() {
	MobileObj::update();
}


PlayerVesselView::PlayerVesselView(PlayerVessel* pv) : MobileObjView(pv) {
	//background.setFillColor(sf::Color(20,60,20)); 
}

void PlayerVesselView::update() {
	MobileObjView::update();
	// shoot weapon
}

