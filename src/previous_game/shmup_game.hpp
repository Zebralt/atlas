#ifndef shmup_game_hpp

#include "../engine/engine_program.hpp"
#include "../engine/engine.hpp"
#include "mobileobj.hpp"

class MobileObj;
class MobileObjView;
class Pattern;
class PlayerVessel;
class PlayerVesselView;
class Level;

class Shmup : public EngineProgram {
public:
	
	std::map<MobileObj*, MobileObjView*> mobile_objs; ///< list of generic mobile objs ; contains bullets and vessels
	
	std::map<std::string, Pattern*> patterns; ///< patterns are generic for now ; here you will find them
	//std::vector<PlayerVessel
	std::vector<std::pair<PlayerVessel*, PlayerVesselView*>> player_vessels; ///< same kind of list as the former, except for the player vessels (2P)
	
	EngineViewport game_viewport; ///< sf::View to draw on a part of  the screen for sfml_app
	
	Level* level = nullptr; ///< contains the game content for this level
	
	int canvas_width; ///< size of  the game canvas
	int canvas_height;

	Shmup(Engine* a);
	
	virtual void start();
	virtual void load(std::string);
    virtual void update();
    virtual void pause();
    virtual void unpause();
    
    void addObject(MobileObj*, MobileObjView*);
    void addPattern(std::string name, Pattern* p);
    Pattern* getPattern(std::string);
    
	/// \brief if the sfml_app doesn't associcate the event to an action, the game can have it
    virtual void eventHandler(sf::Event&);
    
    /// \brief check collisions between mobile objs (should use a collision grid)
    void check_collisions();
    
    /// \brief interpretes mobile obj metadata (see RawWave class)
    void interprete(std::string);
    
    /// \brief introduces a projectile into the game
    void procProjectile(short,std::string,float,float,float,float);
    
    /// \brief introduces a vessel into the game
    void procVessel(MobileObj_MVC);
    
    /// \brief introduces an event into the game
    void procEvent(std::string, std::string);
};


#endif // shmup_game_hpp