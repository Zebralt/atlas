#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <iostream>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "settings.hpp"
#include "../global.hpp"

class Sound;
class Music;

class Widget;
class Blob;
class Sprite;
class Animation;

class Scene;
class Transition;

enum ENGINE_STATE {
 ENGINE_TERMINATED  = 0,
 ENGINE_INMENU      = 0b100000,
 ENGINE_LOADING     = 0b010000,
 ENGINE_INGAME      = 0b001000,
 ENGINE_MAINMENU    = 0b000100,
 ENGINE_LAUNCHING   = 0b000010,
 ENGINE_RUNNING     = 0b000001,
 ENGINE_TRANSITION  = 0b1000000
};

enum RESOURCE_TYPE {
	TEXTURE, SOUND, MUSIC, FONT
};

/// This class handles viewports
struct EngineViewport {
	EngineViewport(sf::View* v = nullptr, int zi = 0) {
		sfview = v;
		z_index = zi;
	}
	sf::View* sfview = nullptr;
	short z_index = 0;
};

bool operator<(const EngineViewport& a, const EngineViewport& b);

class Engine {
public:
	/// SINGLETON 
	static Engine& get() {
		if (!singleton) {
			singleton = new Engine();
		}
		return *singleton;
	}
	static bool init() {
		get().init_engine();
	}
	static void run() {
		get().run_engine();
	}
	static void quit() {
		get().close_engine();
	}
	static int get_status() {
		get().status;
	}
	
	static void load_scene(Scene* s) {
		get().current_scene = s;
	}
	
	static pugi::xml_attribute get_setting(const std::string& name) {
		return get().settings.get(name);
	}
	
	static sf::Texture* create_texture(const std::string& name, const std::string& filepath);
	static bool load(RESOURCE_TYPE type, const std::string& name, const std::string& filepath);
	static void clear();
	
	/// PLAY SOUND OR MUSIC (don't give them the same names !)
	static bool play(const std::string& name);
	
	/// GENERATE SPRITES
	// with a texture
	static Sprite* create_sprite(sf::Texture*);
	static Sprite* create_sprite(sf::Texture*, const Rect&);
	
	// with a texture path
	static Sprite* create_sprite(const std::string& filepath);
	static Sprite* create_sprite(const std::string& filepath, const Rect&);
	static Sprite* create_sprite(const std::string& filepath, const std::string& alpha);
	static Sprite* create_sprite(const std::string& filepath, const Rect&, const std::string& alpha);
	
	///
	
	void load_settings(Settings&);
	
	void handle_events();
		void handle_keyboard_events(sf::Event&);
		void handle_mouse_events(sf::Event&);
			void handle_mouseover_events(sf::Event&);
			void handle_mouseclick_events(sf::Event&);
	
	void update();
	
	void update_screen();
	
	// PLAY A SOUND FROM NAME
	bool play_sound(const std::string& sound);
	// PLAY A MUSIC FROM NAME
	bool play_music(const std::string& name);
	// FADE OUT OF CURRENT MUSIC, FADE IN OF NEXT MSUCI
	void switch_to_music(const std::string& name, int delay = 100);	
	
	/// RESOURCES LOADING
	bool load_texture(const std::string& name, const std::string& path, const std::string& alpha = "");
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
	
	/// ENGINE STATE HANDLING
	// REMOVE STATE FLAG FROM STATE
	void strip_flag(int flag);
	// ADD STATE FLAG TO STATE
	void add_flag(int flag);
	// FORCE STATE TO THIS FLAG AND ONLY THIS FLAG
	void set_flag(int flag);
	
	/// ADD OR REMOVE GRAPHICAL OBJECTS
		
//	void add_blob(Blob* b);
//	void add_blob(EngineViewport v, Blob* b);
//	void add_widget(std::string, Widget*);
//    void remove_widget(std::string);
//    Widget* get_widget(std::string name);
//    std::vector<Widget*>::iterator find_widget(std::string name);
//    std::vector<Widget*>::iterator find_widget(Widget*);

		
private:
	
	/// SFML ELEMENTS
	sf::RenderWindow* window = nullptr;
	
	///./..
	Scene* current_scene = nullptr;
	int status = 1;
	
	/// SETTINGS
	Settings settings;
	
	/// SCREEN OBJECTS
	// LIST OF UI WIDGETS
	// std::vector<Widget*> widgets;
	// LIST OF OTHER OBJECTS (SUCH AS GAME OBJECTS)
	 std::vector<Blob*> blobs;
	 std::vector<Animation*> animations;
    // If you want to have some game objects mouseover or mouseclick -enabled,
    // you'll have to add to the widgets, or rethink this structure
    
    // You might want to have different viewports on your screen
	std::map<EngineViewport, std::vector<Blob*>> view_blobs;
	
	/// IN-MEMORY RESOURCES
	sf::Font global_font; // DEFAULT FONT
    std::map<std::string, sf::Font*> fonts; // ALL FONTS
    std::map<std::string, sf::Texture*> textures; // TEXTURES. Only refer to them in blobs.
    std::map<std::string, Sound*> sounds; // SOUNDS. To be occasionally played.
    std::map<std::string, Music*> musics; // MUSICS. To be played in background.
    
    bool load_global_font(const std::string& path);
    
    /// SINGLETON
    static Engine* singleton;
    Engine();	
    
    /// This must be run first.
	bool init_engine();
	
	/// This must be run next to launch the engine.
	void run_engine();
		
	/// QUIT ALTOGETHER
	void close_engine();
	
	
};

#endif // ENGINE_HPP_