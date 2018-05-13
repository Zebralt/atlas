#ifndef vessels_hpp
#define vessels_hpp

#include "mobileobj.hpp"
#include "../graphics/ui/picture.hpp"

class ShootWave;

/// \brief figures a non-player vessel
class Vessel : public MobileObj {
public:
	Vessel();
	
	ShootWave* shoot_pattern = nullptr; ///< the shoot pattern of the vessel (extends Wave, aka list of meta elements)
	
	/// \brief calls MobileObj::update. Updates shoot pattern
	virtual void update();
	
	void setShootWave(ShootWave* st);
};
	
/// \brief view of the vessel MVC
class VesselView : public MobileObjView {
public:
	VesselView(Vessel*);
	
	/// \brief update coordinates to model position
	virtual void update();
};

/// \brief figures a player vessek
class PlayerVessel : public MobileObj {
public:
	PlayerVessel();
//	void move(float f, float e) { position += sf::Vector2f(speed*f,speed*e); }
	
	///  \brief updates MobileObj base, updates weapon
	void update();
};

class PlayerVesselView : public MobileObjView {
public:
	PlayerVessel* model;
	
	PlayerVesselView(PlayerVessel*);
	
	/// updates coordinates to model position
	void update();
	
};

#endif // vessels_hpp