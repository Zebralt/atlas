#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Settings;
class Sound;
class Music;

enum ENGINE_STATE {
 TERMINATED  = 0,
 INMENU      = 0b100000,
 LOADING     = 0b010000,
 INGAME      = 0b001000,
 MAINMENU    = 0b000100,
 LAUNCHING   = 0b000010,
 RUNNING     = 0b000001,
 TRANSITION  = 0b1000000
};

enum RESOURCE_TYPE {
	TEXTURE, SOUND, MUSIC, FONT
};


class Engine {
public:
	Engine();
	
	void load_settings(Settings&);
	void run();
	void event_catcher();
		void keyboard_events();
		void mouse_events();
			void mouseover_events();
			void mouseclick_events();
	void update();
	
	// PLAY A SOUND FROM NAME
	bool play_sound(const std::string& sound);
	// PLAY A MUSIC FROM NAME
	bool play_music(const std::string& name);
	// FADE OUT OF CURRENT MUSIC, FADE IN OF NEXT MSUCI
	void switch_to_music(const std::string& name, int delay = 100);	
	
	/// RESOURCES LOADING
	bool load_texture(const std::string& name, const std::string& path, const std::string& aplha = "");
	bool load_sound(const std::string& name, const std::string& path);
	bool load_music(const std::string& name, const std::string& path);
	bool load_font(const std::string& name, const std::string& path);
	bool load_resource(const std::string& name, RESOURCE_TYPE resource_type, const std::string& path);
	
	sf::Font* get_global_font();
	sf::Font* get_font(const std::string& name);
	
	sf::Texture* get_texture(const std::string& name);
	Sound* get_sound(const std::string& name);
	Music* get_music(const std::string& name);
	
	/// CLEARING RESOURCES
	bool free_resources();
	bool free_textures();
	void free_sounds();
	void free_musics();
	
	/// QUIT ALTOGETHER
	void quit();
	
	
	/// ENGINE STATE HANDLING
	// REMOVE STATE FLAG FROM STATE
	void strip_flag(int flag);
	// ADD STATE FLAG TO STATE
	void add_flag(int flag);
	// FORCE STATE TO THIS FLAG AND ONLY THIS FLAG
	void set_flag(int flag);
		
private:
	
	/// SETTINGS
//	Settings settings;
	
	/// SCREEN OBJECTS
	// LIST OF UI WIDGETS
//	std::vector<Widget*> widgets;
	// LIST OF OTHER OBJECTS (SUCH AS GAME OBJECTS)
//    std::vector<Blob*> blobs;
    // If you want to have some game objects mouseover or mouseclick -enabled,
    // you'll have to add to the widgets, or rethink this structure
	
	/// IN-MEMORY RESOURCES
	sf::Font global_font; // DEFAULT FONT
    std::map<std::string, sf::Font*> fonts; // ALL FONTS
    std::map<std::string, sf::Texture*> textures; // TEXTURES. Only refer to them in blobs.
    std::map<std::string, Sound*> sounds; // SOUNDS. To be occasionally played.
    std::map<std::string, Music*> musics; // MUSICS. To be played in background.
    
    bool load_global_font(const std::string& path);
	
};

#endif // ENGINE_HPP_