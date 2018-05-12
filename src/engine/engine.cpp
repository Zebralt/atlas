#include "../global.hpp"
#include "engine.hpp"
#include "engine_program.hpp"

#include "../tools/strmanip.hpp"
#include "audio/sound.hpp"

#include <iomanip>

/// 

Engine::Engine() {
    
}

bool Engine::init() {
    /// 1. load settings from XML files
    /// 2. load SFML context settings
    
//    sf::ContextSettings context_settings;
//	context_settings.antialiasingLevel = 8;
//	window = new sf::RenderWindow(sf::VideoMode(settings.resolution.width, settings.resolution.height), "test sfml app",sf::Style::Close,context_settings);
//    keyregister.init();
//    if (!loadGlobalFont("resources/fonts/Roboto-Medium.ttf")) {
//        return false;
//    }

    return true;
}

void Engine::run() {
    /// 1. load engine graph (from program to program) from XML ? I suppose we could do that
    program = new EngineProgramSequence(this);
    /// 2. initialize first program
    program->init();
    /// 3. enter main loop
    while (status && window->isOpen()) {
        handle_events();
        update();
        update_screen();
    }
}

void Engine::update() {
    /// 1. update program
    /// 2. update graphical objects
    /// 3. if they are terminated, delete the object or go to the next program
}

void Engine::update_screen() {
    
    // draw a black background
    window->clear(sf::Color::Black);
    
    /// 1. draw all graphical objects
    /// 2. draw UI widgets atop
    /// 3. draw transition element
    
    window->display();
    
}

/// EVENTS MANAGEMENT //////////////////////////////////////////////////////////////////////////////////////

void Engine::handle_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || !program) {
            status = 0;
            window->close();
            return;
        }

        handle_keyboard_events(event);
        
        handle_mouse_events(event);
        
        program->handle_events(event);
    }
}

void Engine::handle_keyboard_events(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        handle_mouseclick_events(event);
    }
    else if (event.type == sf::Event::MouseMoved) {
        handle_mouseover_events(event);
    }
}

void Engine::handle_mouse_events(sf::Event& event) {

}

void Engine::handle_mouseover_events(sf::Event& event) {

}

void Engine::handle_mouseclick_events(sf::Event& event) {

}

/// RESSOURCES MANAGEMENT //////////////////////////////////////////////////////////////////////////////////

bool Engine::load_global_font(const std::string& path) {
    return global_font.loadFromFile(path);
}

sf::Font* Engine::get_global_font() {
    return &global_font;
}

sf::Font* Engine::get_font(const std::string& name) {
    if (fonts.find(name) != fonts.end()) {
        return fonts[name];
    }
    else {
        return &global_font;
    }
}

bool Engine::load_font(const std::string& name, const std::string& path) {
    sf::Font* newfont = new sf::Font();
    if (newfont->loadFromFile(path)) {
        fonts[name] = newfont;
        return true;
    }
    else return false;
}

bool Engine::load_texture(const std::string& name, const std::string& path, const std::string& alphakey) {
	
//	if (name == "") {
//		std::vector<std::string> elems = split(split(path,'.')[0],'/');
//		name = elems[elems.size()-1];
//	}
	LOG("loading texture<" << name << ">");
	sf::Texture* tex = new sf::Texture;
    if (alphakey == "") {
		if (tex->loadFromFile(path)) {
			textures[name] = tex;
			return true;
		}
    }
    else {
		std::cout << alphakey << std::endl;
		std::vector<std::string> rgbs = split(alphakey,',');
		sf::Color color(std::stoi(rgbs[0]),std::stoi(rgbs[1]),std::stoi(rgbs[2]));		
		sf::Image image;
		if (image.loadFromFile(path)) {
			image.createMaskFromColor(color);
			if (tex->loadFromImage(image)) {
				textures[name] = tex;
				return true;
			}
		}
    }
	return false;
}

sf::Texture* Engine::get_texture(const std::string& name) {
    if (textures.find(name) != textures.end()) {
        return textures[name];
    }
    else {
		LOG("Engine message: couldn't find texture " << name);
        return nullptr;
    }
}

bool Engine::load_sound(const std::string& name, const std::string& path) {
    /*sf::SoundBuffer sb;
    sf::Sound* sou = new sf::Sound;
    if (sb.loadFromFile(path)) {
        sou->setBuffer(sb);
        sounds[name] = sou;
        return true;
    }
    else {
        return false;
    }*/
    Sound* sou = new Sound(path);
    sounds[name] = sou;
    sou->set_volume(50);
    return true;
}

Sound* Engine::get_sound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        return sounds[name];
    }
    else {
		LOG("Engine message: couldn't find sound " << name);
        return nullptr;
    }
}

bool Engine::load_music(const std::string& name, const std::string& path) {
	musics[name] = new Music(path);
	musics[name]->setVolume(50);
	return true;
}

Music* Engine::get_music(const std::string& name) {
    if (musics.find(name) != musics.end()) {
        return musics[name];
    }
    else {
		LOG("Engine message: couldn't find music " << name);
        return nullptr;
    }
}

bool Engine::play_sound(const std::string& name) {
    if (sounds.find(name) != sounds.end()) {
        sounds[name]->play();
        return true;
    }
    else {
		LOG("couldn't find sound " << name);
		return false;
    }
}

bool Engine::play_music(const std::string& name) {
    if (musics.find(name) != musics.end()) {
        musics[name]->play();
        return true;
    }
    return false;
}

bool Engine::free_textures() {
    for (std::map<std::string, sf::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it) {
        delete(it->second);
    }
    textures.clear();
    
    return true;
}

bool Engine::free_resources() {
    PRINT(std::setw(20) << "freeing fonts :(" << fonts.size() << ")");
    for (std::map<std::string, sf::Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it) {
        delete(it->second);
    }
    fonts.clear();
    LOG("OK");
    
	PRINT(std::setw(20) << "freeing textures :(" << textures.size() << ")");
    free_textures();
    LOG("OK");
    
    PRINT(std::setw(20) << "freeing sounds :(" << sounds.size() << ")");
    for (std::map<std::string, Sound*>::iterator it = sounds.begin(); it != sounds.end(); ++it) {
        delete(it->second);
    }
    sounds.clear();
    LOG("OK");
    
    PRINT(std::setw(20) << "freeing musics :(" << musics.size() << ")");
    for (std::map<std::string, Music*>::iterator it = musics.begin(); it != musics.end(); ++it) {
        delete(it->second);
    }
    musics.clear();
    LOG("OK");
    
    return true;
}

/// QUIT

void Engine::quit() {
	free_resources();
	exit(0);
}