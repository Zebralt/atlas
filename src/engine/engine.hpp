#ifndef ENGINE_HPP_
#define ENGINE_HPP_

/// C++ Headers
#include <iostream>
#include <map>
#include <vector>

/// SFML headers
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/// Proprietary headers
#include "settings.hpp"
#include "../global.hpp"

// ^Please follow this order of headers includes.
// Indentation is of 4 spaces.

class Sound;
class Music;

class Widget;
class Blob;
class Sprite;
class Animation;

class Scene;
class Transition;

/// \brief This enumeration contains all possible states
/// for the engine to find itself in, as to determine which
/// behavior to adopt.
/// For example, if `status = ENGINE_INMENU`, it will assume
/// that a menu is focused, so the arrows may be used to cycle
/// through the menu's items, and 'Enter' to select an item.
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

/// \brief This class handles viewports. This is a rather complex
/// but very important feature of SFML, and ultimately of the Engine.
struct EngineViewport {
	EngineViewport(sf::View* v = nullptr, int zi = 0) {
		sfview = v;
		z_index = zi;
	}
	sf::View* sfview = nullptr;
	short z_index = 0;
};

bool operator<(const EngineViewport& a, const EngineViewport& b);

/**
	\author Zebralt
	\brief This is the main class figuring the engine. The Engine class
	manages resources (textures, sounds, fonts, musics. It is the main 
	interface to the engine features. As there is no need for more than
	one object of this class, and to render access to methods and parameters
	easier, it follows the Singleton design pattern. You can access the 
	singleton object with `get()`. 
	To use the engine, you need to call `init()` first. This will load 
	settings and initialize the SFML interface. Next, you can load a scene
	with `load_scene(Scene*)`. If you do not, a default scene will be started
	up instead. Finally, you may start the engine with `run()`. The engine
	will proceed with the loaded scene. Afterwards, you can retrieve the engine
	end status with `get_status()`.
	
*/
class Engine {
public:
	/// SINGLETON 
	
	/// \brief Returns the singleton object of the class Engine.
	/// It will be initialized if not already created.
	static Engine& get() {
		if (!singleton) {
			singleton = new Engine();
		}
		return *singleton;
	}
	
	/// \brief Initializes the engine.This will load settings from a XML file 
	/// (currently 'settings.xml', sitting at the root of the project) and
	/// initialize the SFML interface (context settings and render window).
	static bool init() {
		return get().init_engine();
	}
	
	/// \brief This method contains the main loop of the engine. If no scene
	/// was loaded, a default scene will be.
	/// TODO Interesting point : should we do the time interval (you know, 60 fps,
	/// 17 ms) upstream, in the main loop ? Because for now, it is done separately
	/// by all time-enabled objects.
	static void run() {
		return get().run_engine();
	}
	
	/// \brief This will forcefully quit the engine and close the program.
	/// Resources will be freed before quitting.
	static void quit() {
		get().close_engine();
	}
	
	/// \brief Returns engine status.
	static int get_status() {
		return get().status;
	}
	
	/// \brief Loads a scene.
	static void load_scene(Scene* s) {
		get().current_scene = s;
	}
	
	static pugi::xml_attribute get_setting(const std::string& name) {
		return get().settings.get(name);
	}
	
	
	/// \brief This is the interval (in milliseconds) between each update iteration.
	/// As it is needed outside of the Engine class, notably to compute animations variables,
	/// it is accessible as static. public or not public ? One can wonder.
	static int update_interval;
	
	/// \brief This allows to load a texture from a filepath, registering it under a 
	/// name from which it can be called upon later.
	static sf::Texture* create_texture(const std::string& name, const std::string& filepath);
	
	/// \brief This method will call the appropriate resource loading function depending on the 
	/// resource type parameter.
	static bool load(RESOURCE_TYPE type, const std::string& name, const std::string& filepath);
	
	/// \brief This method will call the appropriate resource getter depending on resource type.
	static sf::Texture* get_texture(const std::string& name) { return get()._get_texture(name); }
	static sf::Font* get_font(const std::string& name) { return get()._get_font(name); }
	static Sound* get_sound(const std::string& name) { return get()._get_sound(name); }
	static Music* get_music(const std::string& name) { return get()._get_music(name); }
	static sf::Font* get_global_font() { return get()._get_global_font(); }
	
	///\brief Clears and frees all resources.
	static void clear();
	
	/// \brief Play sound or music. (don't give them the same names !) or, just do two methods dumbass
	static bool play(const std::string& name);
	
	/// \brief Creates a sprite from a texture. Either one you have loaded yourself, or you retrieved
	/// in the engine's resources.
	static Sprite* create_sprite(sf::Texture*);
	
	/// \brief Creates a sprite from a texture. Allows to specify a subpart of the texture to use.
	/// The texture rectangle can be changed later in the Sprite class methods.
	static Sprite* create_sprite(sf::Texture*, const Rect&);
	
	/// \brief Creates a sprite by loading a texture, killing two birds in one stone. The texture
	/// will be loaded and stored by the engine. You can reuse it later.
	static Sprite* create_sprite(const std::string& filepath);
	
	/// \brief Creates a sprite by loading a texture. Allows you to specify the texture canvas.
	static Sprite* create_sprite(const std::string& filepath, const Rect&);
	
	/// \brief Creates a sprite by loading a texture. Allows to load a texture with a specific
	/// alpha parameter.
	static Sprite* create_sprite(const std::string& filepath, const std::string& alpha);
	
	/// \brief Creates a sprite by loading a texture. Allows to load a texture with a specific
	/// alpha parameter, and specify which part of the texture to use.
	static Sprite* create_sprite(const std::string& filepath, const Rect&, const std::string& alpha);
	
	static void register_widget(const std::string& name, Widget* widget);
	static void register_widget(Widget* widget);
	static void register_blob(const std::string& name, Blob* b);
	static void register_blob(Blob* b);
	
	static Widget* get_widget(const std::string& name);
	
	static Vec2 get_mouse_position() {
		return mouse_position;
	}
	
//	void load_settings(Settings&);
	
	/// \brief Receives events from the SFML interface. Events are sent downstream to the scene
	/// and to the specific methods for event types.
	void handle_events();
		void handle_keyboard_events(sf::Event&);
		void handle_mousemove_events(sf::Event&);
		void handle_mouseover_events(sf::Event&);
		void handle_mouseclick_events(sf::Event&);
	
	/// \brief Updates the scene and the stored elements.
	void update();
	
	/// \brief Updates the screen. Draws the scene.
	void update_screen();
	
	/// \brief Plays a sound from name. It must have been loaded and registered by the engine first.
	bool play_sound(const std::string& sound);
	
	/// \brief Plays a music from name. It must have been loaded and registered by the engine first.
	bool play_music(const std::string& name);
	
//	void switch_to_music(const std::string& name, int delay = 100);	
	
	/// \brief Loads a texture from a filepath and registers it under a name. You can specify an alpha
	/// parameter to render one color transparent in the texture (Doesn't work very well, I'm afraid).
	bool load_texture(const std::string& name, const std::string& path, const std::string& alpha = "");
	
	/// \brief Loads a sound from a filepath and registers it under a name. 
	bool load_sound(const std::string& name, const std::string& path);
	
	/// \brief Loads a music track from a filepath and registers it under a name. 
	bool load_music(const std::string& name, const std::string& path);
	
	/// \brief Loads a font from a filepath and registers it under a name. 
	bool load_font(const std::string& name, const std::string& path);
	
	/// \brief Loads a generic resource from a filepath and registers it under a name. 
	bool load_resource(const std::string& name, RESOURCE_TYPE resource_type, const std::string& path);
	
	/// \brief Returns the global font of the engine. Global and default.
	sf::Font* _get_global_font();
	
	/// \brief Returns a registered font by name.
	sf::Font* _get_font(const std::string& name);
	
	/// \brief Returns a registered texture by name.
	sf::Texture* _get_texture(const std::string& name);
	
	/// \brief Returns a registered sound by name.
	Sound* _get_sound(const std::string& name);
	
	/// \brief Returns a registered music by name.
	Music* _get_music(const std::string& name);
	
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
		
	void add_blob(Blob* b);
//	void add_blob(EngineViewport v, Blob* b);
	void add_widget(const std::string& name, Widget*);
	void add_widget(Widget*);
    void remove_widget(const std::string&);
    Widget* _get_widget(const std::string& name);
    std::vector<Widget*>::iterator find_widget(const std::string& name);
    std::vector<Widget*>::iterator find_widget(Widget*);

		
private:
	
	/// SFML ELEMENTS
	sf::RenderWindow* window = nullptr;
	
	///./..
	Scene* current_scene = nullptr;
	int status = 1;
	
	/// SETTINGS
	Settings settings;
	
	/// SCREEN OBJECTS
	// LIST OF UI WIDGETS and mouse-enabled objects ...
	std::vector<Widget*> widgets;
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
    static Vec2 mouse_position;
    Engine();	
    
    /// This must be run first.
	bool init_engine();
	
	/// This must be run next to launch the engine.
	void run_engine();
		
	/// QUIT ALTOGETHER
	void close_engine();
	
	
};

#endif // ENGINE_HPP_