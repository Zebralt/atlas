#ifndef patterns_hpp
#define patterns_hpp

#define PI 3.14159265359

#include <SFML/System/Vector2.hpp>
#include "../model/temporary.hpp"

/// should patterns be tied to one object ? or be generic
/// for now they're generic
class Pattern {
public:
	virtual float f(float x);
	virtual sf::Vector2f nextPoint(sf::Vector2f previous_point, float speed, float angle);
	virtual sf::Vector2f nextVector(float,float);
};

class MobileObj;

/// This is the class that ties pattern and mobile object
class Trajectory : public Temporary {
public:
	Trajectory(Pattern*, int);
	
	virtual void update();
	MobileObj* target = nullptr;
	Pattern* pattern = nullptr;
	
	float distance = 0;
	float maxDistance = 0;
	
	void setTarget(MobileObj*);
	float angle;
};

/// laser => (p1, p2) be its ends
/// if we see it as a regular pattern moving only one point, then:
/// 	p1 is tied to one spot,
///		p2 is the one moving
class LaserPattern : public Pattern {

};

//https://gamedev.stackexchange.com/questions/39931/fast-accurate-2d-collision
//
//class CollisionGrid {
//public:
//	int discretize = 4;
//	std::vector<MobileObj*>** grid;
//	
//	CollisionGrid();
//	CollisionGrid(int);
//	
//	
//};

#endif // patterns_hpp