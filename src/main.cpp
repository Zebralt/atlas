#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "engine/engine.hpp"
#include "game/snake_game/snake_game.hpp"
#include "engine/pipeline.hpp"

#include "game/show_cards/show_cards.hpp"

#include "../test/test.hpp"

#include <windows.h>

#include "engine/pipeline.hpp"

int test_SFML();

int main() {
    
//    run_tests();
//    Engine::init();//"resources/show_cards/settings.xml");
//    Engine::load_scene(new SnakeGameScene(10,10));
////    Engine::load_scene(new ShowCardsScene());
//    Engine::run();
//    
//    return Engine::get_status();
    
    auto pipeline = new EnginePipeline("engine_pipeline.xml");
    
    LOG(*pipeline);
    
    pipeline->run();
    
    return pipeline->data();
    
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
    
    return 0;
}