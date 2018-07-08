#include "global.hpp"

#include "sound.hpp"

// namespace atlas_engine {
//    namespace Audio {

Sound::Sound() {}

Sound::Sound(const std::string& path) {
    load_from_file(path);
}

bool Sound::load_from_file(const std::string& filepath) {
    if (buffer.loadFromFile(filepath)) {
        sound.setBuffer(buffer);
        return true;
    }
    else {
        LOG("couldn't load " + filepath);
        return false;
    }
}

sf::Sound* Sound::get() {
    return &sound;
}

void Sound::play() {
    sound.play();
}

void Sound::pause() {
    sound.pause();
}

void Sound::stop() {
    sound.stop();
}

void Sound::set_volume(const float& f) {
    sound.setVolume(f);
}

/////////////////

Music::Music() : sf::Music() {
	
}

Music::Music(const std::string& path) : sf::Music() {
	openFromFile(path);
}

void Music::update() {

}

//} 
// } // namespace Audio