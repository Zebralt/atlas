#include <iostream>
#include <SFML/Graphics.hpp>
#include "mobileobj.hpp"
#include "patterns.hpp"


MobileObj::MobileObj() {
//	setStatus(IDLE);
}

void MobileObj::update() {
	if (status == RUNNING) {
		if (/*!trajectory || trajectory->getStatus() == TERMINATED ||*/ (phasing_counter <= 0 && phasing == OFFSCREEN)) {
			status = TERMINATED;
		}
		else if (trajectory && trajectory->getStatus() == RUNNING) {				
			trajectory->update();
		}
	}
}

void MobileObj::setTrajectory(Trajectory* t) {
	t->target = this;
	trajectory = t;
}

void MobileObj::move(sf::Vector2f v) {
	position += v;
}

void MobileObj::setPhasing(Phasing i) {
	if (i != phasing) {
		if (i == OFFSCREEN) {
			phasing_counter--;
		}
		else {
		}
		phasing = i;
//		LOG(this << "is now " << (phasing == ONSCREEN?"ONSCREEN":"OFFSCREEN") << "(" << phasing_counter << ")");
	}
}

MobileObj::~MobileObj() {
	delete(trajectory);
}

/////////////////////////////////////

MobileObjView::MobileObjView(MobileObj* m) : Picture() {
	model = m;
}

void MobileObjView::update() {
	Picture::update();
	if (status == RUNNING) {
		// get position	
		setPosition(sf::Vector2f(model->position.x,model->position.y)-sf::Vector2f(width/2, height/2));
//		LOG("model_position=" << model->position.x << ":" << model->position.y);
//		LOG("view_position=" << position.x << ":" << position.y);
		//get orientation
		if (rotation != model->orientation) {
//			LOG("sprite:" << rotation);
//			LOG("model:" << model->orientation);
//			transform.rotate(model->orientation - rotation, model->position);
			rotation = model->orientation;
		
		}
		transform = sf::Transform();
		transform.rotate(rotation, model->position);
		
		if (!model || model->getStatus() == TERMINATED) {
			status = TERMINATED;
			return;
		}
	}
	// TERMINATED condition = out of screen ?
}

void MobileObjView::setPosition(sf::Vector2f v) {
	Blob::setPosition(v);
	// admitting that sprites/textures are pointing UPWARDS by default (automatic 180o rotation)
	m_sprite.setPosition(sf::Vector2f(position.x, position.y));
}

/*
#include "pattern.hpp"

	sf::Vector2f operator/(sf::Vector2f v, float f) {
		return sf::Vector2f(v.x/f,v.y/f);
	}

	int random(int a, int b) {
		return rand()%(b-a)+a;
	}

	MobileObj::MobileObj() {
		shape = sf::CircleShape(3.f);
		shape.setFillColor(sf::Color(random(100,255),random(100,255),random(100,255)));
		//shape.setFillColor(sf::Color::Magenta);
		//shape.setOutlineColor(sf::Color::White);
		//shape.setOutlineThickness(1);
		width = 16;
		height = 14;
		hitbox = sf::RectangleShape(sf::Vector2f(width,height));
		hitbox.setFillColor(sf::Color::Blue);
		pattern = NULL;
	}

	sf::Vector2f MobileObj::getPosition() {
		return position;
	}

	void MobileObj::setPosition(sf::Vector2f v) {
		position = v;
		shape.setPosition(position-sf::Vector2f(shape.getRadius()/2,shape.getRadius()/2));
		sprite.setPosition(position-sf::Vector2f(width/2,height/2));
		hitbox.setPosition(position - hitbox.getSize()/2);
	//	sprite.setPosition(position);
	}

	void MobileObj::setPosition(float x, float y) {
		setPosition(sf::Vector2f(x,y));
	}

	void MobileObj::update() {
		if (pattern) {
			pattern->update();
		}
	}

	void MobileObj::setPattern(Pattern& p) {
		pattern = &p;
		//p.setTarget(*this);
	}

	Pattern& MobileObj::getPattern() {
		if (!pattern) {
			std::cout << "No pattern defined!" << std::endl;
		}
		return *pattern;
	}

	void MobileObj::setTexture(sf::Texture& t) {
		sprite.setTexture(t);
	}

	void MobileObj::setScale(float x, float y) {

		sf::Vector2f targetSize(x,y);
		width = x;
		height = y;
		sprite.setScale(
		targetSize.x / sprite.getLocalBounds().width,
		targetSize.y / sprite.getLocalBounds().height);
		setPosition(position);
	}

	void MobileObj::setRotation(float f) {
		//sprite.setOrigin(position);
		sprite.setRotation(0);
		sprite.rotate(-f);
		hitbox.setRotation(0);
		hitbox.rotate(-f);
		//sprite.setOrigin(sf::Vector2f(0,0));
	}

	void MobileObj::setRadius(float f) {
		shape.setRadius(f);
	}
*/

void MobileObj::setPosition(sf::Vector2f v) {
	position = v;
}