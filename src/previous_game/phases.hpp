#ifndef phases_hpp
#define phases_hpp

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../model/temporary.hpp"
#include "../engine/time/timer.hpp"

class Phase;
class RawWave;
class Wave;
class Shmup;
class MobileObj;
class MobileObj_MVC;

/// A stage decomposes in phases ; 
class Level : public Temporary {
public:
	Level(Shmup* s);
	Shmup* game;
	
	std::string name;
	short difficulty;
	short phase_counter = 0;
	std::vector<Phase*> phases;
	
	Level(Shmup*,std::string);
	
	void loadFromFile(std::string path);
	virtual void update();
	virtual void terminate();
	virtual void addPhase(Phase* p);
    
    /// \brief wip
    MobileObj_MVC getVesselFromType(int i);
	
	MobileObj_MVC getPelletFromType(int i);
    
    void getPatternFromType(int i);

	void getPatternFromName(std::string g);
};

/// A stage phase can be :
/// - waves of enemies (the current wave can be blocking, or allow next wave to collide)

class Phase : public Temporary {
public:
};

class CombatPhase : public Phase {
public:
	std::vector<Wave*> waves;
	short wave_counter;
	virtual void update();
	void addWave(Wave* w);
};

class QuietPhase : public Phase {
public:
	virtual void update();
};



class BossStage {
	
};

class BossPhase : public Phase {
public:
	std::vector<BossStage*> stages;
};

class Wave : public Temporary, public TimeEnabled {
public:
	Shmup* game = nullptr;
	RawWave* raw = nullptr;
	int next_moment = 0;
	
	Wave(Shmup*);
	Wave(RawWave*, Shmup*);
	
	void extend(RawWave*);
	virtual void update();
	void pause();
	void unpause();
	void start();
};

class Vessel;

class ShootWave : public Wave {
public:
	Vessel* master = nullptr;
	sf::Vector2f offset;
	
	ShootWave(Vessel*, Shmup*);
	ShootWave(Vessel*, RawWave*, Shmup*);
	
	void update();
};

#endif // phases_hpp