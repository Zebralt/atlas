#ifndef SOUND_HPP_
#define SOUND_HPP_

#include "model/temporary.hpp"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>

// namespace atlas_engine {
//namespace Audio {

/**
	\author Zebralt
	\brief This class acts as a wrapper for the sf::Sound/sf::SoundBuffer
	system provided by the SFML.
*/
class Sound {
    sf::Sound sound;
    sf::SoundBuffer buffer;
    
public:
    Sound();
    Sound(const std::string& filepath);
    
    bool load_from_file(const std::string& filepath);
    
    void play();
    void pause();
    void stop();
    
    void set_volume(const float&);
    sf::Sound* get();
};

class MusicEffect;

/**
	\author Zebralt
	\brief This class acts as a wrapper for the sf::Music system
	provided by the SFML. It can be expanded to include various
	music effects, such as automating volume shifting.
	WIP
*/
class Music : public Temporary, public sf::Music {
	std::vector<MusicEffect*> effects;
public:
 	
	Music();
	Music(const std::string&);
	
	void add_effect(MusicEffect* me);
	void update();
};

//} 
// } // namespace Audio

#endif // SOUND_HPP_