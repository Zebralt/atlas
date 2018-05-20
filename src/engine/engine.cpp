#include "../global.hpp"
#include "engine.hpp"
#include "scene.hpp"

#include "../tools/strmanip.hpp"
#include "audio/sound.hpp"

/// UI
#include "../graphics/ui/widget.hpp"
#include "../graphics/ui/panel.hpp"

#include <iomanip>

/// 

Engine* Engine::singleton = nullptr;
int Engine::update_interval = 17;
Vec2 Engine::mouse_position = Vec2();


Engine::Engine() {
    
}

/// STATIC METHODS

bool Engine::load(RESOURCE_TYPE type, const std::string& name, const std::string& filepath) {
    return get().load_resource(name, type, filepath);
}

bool Engine::play(const std::string& name) {
    bool a = false;
    return a = get().play_music(name) ? a : get().play_sound(name); 
}

void Engine::clear() {
    get().free_resources();
}

/// SPRITE GENERATION

 Sprite* Engine::create_sprite(sf::Texture* tex) {
    auto sp = new Sprite();
    // TODO add it to blobs
    sp->setTexture(tex);
    return sp;
}

Sprite* Engine::create_sprite(sf::Texture* tex, const Rect& r) {
    auto sp = new Sprite();
    // TODO add it to blobs
    sp->setTexture(tex, r);
    return sp;
}

// with a texture path
Sprite* Engine::create_sprite(const std::string& filepath) {
        if (load(TEXTURE, filepath, filepath)) {
        return create_sprite(get().get_texture(filepath));
    }
    else 
        return nullptr;
}

 Sprite* Engine::create_sprite(const std::string& filepath, const Rect& rect) {
    if (load(TEXTURE, filepath, filepath)) {
        return create_sprite(get().get_texture(filepath), rect);
    }
    else 
        return nullptr;
}

Sprite* Engine::create_sprite(const std::string& filepath, const std::string& alpha) {
    if (get().load_texture(filepath, filepath, alpha)) {
        return create_sprite(get().get_texture(filepath));
    }
    else 
        return nullptr;
}
Sprite* Engine::create_sprite(const std::string& filepath, const Rect& rect, const std::string& alpha) {
    if (get().load_texture(filepath, filepath, alpha)) {
        return create_sprite(get().get_texture(filepath), rect);
    }
    else 
        return nullptr;
}

void Engine::register_widget(const std::string& name, Widget* widget) {
    if (widget) {
        get().add_widget(name, widget);
    }
}

void Engine::register_widget(Widget* widget) {
    if (widget) {
        get().add_widget(widget);
    }
}

void Engine::register_blob(Blob* blob) {
    if (blob) {
        get().add_blob(blob);
    }
}

Widget* Engine::get_widget(const std::string& name) {
    return get()._get_widget(name);
}
	
/// NON-STATIC METHODS

bool Engine::init_engine() {
    /// 1. load settings from XML files
    settings.load_from_file("settings.xml");
    /// 2. load SFML context settings
    
    sf::ContextSettings context_settings;
	context_settings.antialiasingLevel = 8;
	window = new sf::RenderWindow(sf::VideoMode(settings.as_int("video/resolution/width"), settings.as_int("video/resolution/height")), "test sfml app",sf::Style::Close,context_settings);
//    keyregister.init();
    if (!load_global_font("resources/fonts/Roboto-Medium.ttf")) {
        return false;
    }

    return true;
}

void Engine::run_engine() {
    /// 1. load engine graph (from program to program) from XML ? I suppose we could do that
    if (!current_scene) {
        /// load default scene
        current_scene = new EngineLogoScene();
    }
    /// 2. initialize first program
    if (current_scene) current_scene->initialize();
    else {
        LOG("There is no scene to run. Exiting.");
        quit();
    }
    /// 3. enter main loop
    while (status && window->isOpen()) {
        handle_events();
        update();
        update_screen();
    }
}

void Engine::update() {
    
    if (current_scene) current_scene->update();
    
    update_or_delete(blobs);
    update_or_delete(animations);
}

void Engine::update_screen() {
    
    // draw a black background
    window->clear(sf::Color::White);
    
    window->draw(*current_scene);
    
    /// 1. draw all graphical objects
    /// 2. draw UI widgets atop
    /// 3. draw transition element
    
    window->display();
    
}

/// EVENTS MANAGEMENT //////////////////////////////////////////////////////////////////////////////////////

void Engine::handle_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        
        if (event.type == sf::Event::Closed || !current_scene) {
            status = 0;
            window->close();
            return;
        }

        mouse_position = sf::Mouse::getPosition(*window);
        
        
        // if keyboard event
        handle_keyboard_events(event);
//        handle_mouse_events(event);
        
        // if mouse move event
        if (event.type == sf::Event::MouseMoved)
            handle_mousemove_events(event);
        
        // if mouse click event
        if (event.type == sf::Event::MouseButtonPressed)
            handle_mouseclick_events(event);
        
        current_scene->handle_events(event);
    }
}

void Engine::handle_keyboard_events(sf::Event& event) {

}

void Engine::handle_mousemove_events(sf::Event& event) {
    handle_mouseover_events(event);
}

void Engine::handle_mouseover_events(sf::Event& event) {
    
    for (auto& widget : widgets) {
        if (!widget) continue;
        
        bool mouseover = widget->getRect().contains(Engine::get_mouse_position());
        
        if (!widget->getHover() && mouseover) {
            widget->setHover(true);
            widget->onMouseEnter();
        }
        else if (widget->getHover() && !mouseover) {
            widget->setHover(false);
            widget->onMouseLeave();
        }
    }
    
}

void Engine::handle_mouseclick_events(sf::Event& event) {

// Going backward and breaking at top most widget receiving the click

    // weird loop isn't it ? not sure if safe
    for (auto it = widgets.end() - 1; it != widgets.begin() - 1; --it) {
        auto widget = *it;
        
        if (!widget) continue;
        // assuming mouseovers have been computed beforehand
        if (widget->getHover()) {
            widget->onClick();
            break;
        }
    }
}

/// RESSOURCES MANAGEMENT //////////////////////////////////////////////////////////////////////////////////

bool Engine::load_global_font(const std::string& path) {
    return global_font.loadFromFile(path);
}

sf::Font* Engine::_get_global_font() {
    return &global_font;
}

sf::Font* Engine::_get_font(const std::string& name) {
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

sf::Texture* Engine::_get_texture(const std::string& name) {
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

Sound* Engine::_get_sound(const std::string& name) {
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

bool Engine::load_resource(const std::string& name, RESOURCE_TYPE resource_type, const std::string& path) {
    switch (resource_type) {
    case SOUND:
        return load_sound(name, path);
    case MUSIC:
        return load_music(name, path);
    case TEXTURE:
        return load_texture(name, path);
    case FONT:
        return load_font(name, path);
    }
    
    return 0;
}

Music* Engine::_get_music(const std::string& name) {
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

/// MANAGING GRAPHICAL OBJECTS


void Engine::add_blob(Blob* b) {
    blobs.push_back(b);
}
//
//void Engine::add_blob(EngineViewport v, Blob* b) {
////	view_blobs.insert(std::pair<AppView, std::vector<Blob*>>(v,std::vector<Blob*>()));
//	view_blobs[v].push_back(b);
//}
//

std::vector<Widget*>::iterator Engine::find_widget(const std::string& name) {
    for (std::vector<Widget*>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
        if ((*it)->getName() == name) {
            return it;
        }
    }
    return widgets.end();
}

std::vector<Widget*>::iterator Engine::find_widget(Widget* w) {
    for (std::vector<Widget*>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
        if ((*it) == w) {
            return it;
        }
    }
    return widgets.end();
}

Widget* Engine::_get_widget(const std::string& name) {
    for (std::vector<Widget*>::iterator it = widgets.begin(); it != widgets.end(); ++it) {
        if ((*it)->getName() == name) {
            return *it;
        }
    }
    return nullptr;
}

std::string alterName(const std::string& name) {
    std::string result = name;
    if (result[result.length()-1] >= '0' && result[result.length()-1] <= '9') {
        if (result[result.length()-1] == '9') {
            return result+"0";
        }
        else {
            result[result.length()-1]++;
            return result;
        }
    }
    else {
        return result+"0";
    }
}

void Engine::add_widget(const std::string& name, Widget* w) {
//    LOG("added widget<"  << name << ">");
    w->setName(name);
    /*if (Widget* aw = containsWidget(name)) {
        std::vector<Widget*>::iterator it = findWidget(aw);
        if (it != widgets.end())
            widgets.erase(it);
        delete(aw);
    }*/
    std::string alt_name = name;
    while(Widget* aw = _get_widget(alt_name)) {
        alt_name = alterName(alt_name);
        w->setName(alt_name);
    }
    widgets.push_back(w);
    if (w->hash_code() & CONTAINER) {
//        LOG(w->getName() << " is a container:size = " << ((Panel*)w)->getItems().size());
        ((Panel*)w)->move_in(this);
        //Panel* cont = (Panel*) w;
        //for (uint i=0; i<cont->items.size(); i++) {
        //    addWidget(cont->items[i]->getName(), cont->items[i]);
        //    
        //}*/
    }
}

void Engine::add_widget(Widget* w) {
    if (w) add_widget(w->getName(), w);
}

//
//void Engine::remove_widget(std::string name) {
////    display(widgets);
//    std::vector<Widget*>::iterator it = find_widget(name);
//    Widget* wc = get_widget(name);
//    if (wc && it != widgets.end()) {
//        // if container
//        if (wc->hash_code() & CONTAINER) {
//            ((Panel*)wc)->move_out(this);
//           /* std::vector<Widget*> items = ((Panel*) wc)->getItems();
//            for (uint i=0; i<items.size(); i++) {
//                removeWidget(items[i]->getName());
//            }*/
//        }
//        delete(wc);
//        widgets.erase(it);
////        LOG("removed widget <" << name << ">");
//    }
//    else LOG("couldn't remove widget<" << name << "> because : " << (!wc?"wc null":it == widgets.end()?"it == end":"unknown reason"));
//}


/// QUIT

void Engine::close_engine() {
	free_resources();
	exit(0);
}

/// OTHERS
bool operator<(const EngineViewport& a, const EngineViewport& b) {
	return a.z_index < b.z_index;
}