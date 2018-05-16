#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "engine/engine.hpp"
#include "game/snake_game/snake_game.hpp"
#include <windows.h>

int test_SFML();

int main() {
    Engine::init();
//    Engine::load_scene(new SnakeGameScene(10,10));
    Engine::run();
    return Engine::get_status();
}

int test_SFML() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    sf::Font font;
    font.loadFromFile("");
        
    sf::SoundBuffer buffer;
// on charge quelque chose dans le buffer...
    buffer.loadFromFile("resources/theircoming.ogg");

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    
    Sleep(1000);

    sf::Music music;
    if (!music.openFromFile("resources/theircoming.ogg"))
        return -1; // erreur
    music.play();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}