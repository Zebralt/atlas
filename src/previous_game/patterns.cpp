#include "patterns.hpp"
#include "mobileobj.hpp"
#include <cmath>

sf::Vector2f rotateVector(sf::Vector2f v,float angle) {
	angle = -(angle*PI)/180;
	sf::Vector2f tmp;
	tmp.x = v.x*cos(angle) - v.y*sin(angle);
	tmp.y = v.x*sin(angle) + v.y*cos(angle);
	return tmp;
}

sf::Vector2f Pattern::nextPoint(sf::Vector2f previous_point, float speed, float angle) {
	return previous_point +	nextVector(speed,angle);
}

sf::Vector2f Pattern::nextVector(float speed, float angle) {
	sf::Vector2f b = rotateVector(sf::Vector2f(0,speed), angle);
	return b;
}

float Pattern::f(float x) {
	float y = 1*x;
	return y;
}

/////////////////////

Trajectory::Trajectory(Pattern* p, int destination) {
	maxDistance = destination;
	pattern = p;
}

void Trajectory::update() {
	if (status == RUNNING) {
		if (target && distance < maxDistance) {
//			target->setPosition(pattern->nextPoint(target->position, target->speed, target->orientation));
			sf::Vector2f nv = pattern->nextVector(target->speed, 180 - target->orientation);
//			std::cout << "newpoint=" << target->position.x << ":" << target->position.y << " to ";
//			std::cout << "(" << nv.x << ":" << nv.y << ")"; 
			target->move(nv);
//			std::cout << "newpoint=" << target->position.x << ":" << target->position.y << std::endl;
			distance += target->speed;
		}
		else {
			LOG("pattern terminated because : " << target << " or " << (distance < maxDistance));
			status = TERMINATED;
		}	
	}
}

void Trajectory::setTarget(MobileObj* mo) {
	target = mo;
}