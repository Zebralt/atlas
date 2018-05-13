#ifndef pellet_hpp
#define pellet_hpp

#include "mobileobj.hpp"

class Pellet : public MobileObj {
public:
	Pellet();
};

class PelletView : public MobileObjView {
public:
	PelletView(Pellet*);
};

class Laser : public Pellet {
public:
	sf::VertexArray points;
};

#endif // pellet_hpp