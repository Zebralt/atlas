#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
//    sf::SoundBuffer buffer;
//// on charge quelque chose dans le buffer...
//    buffer.loadFromFile("../resources/theircoming.ogg");
//
//    sf::Sound sound;
//    sound.setBuffer(buffer);
//    sound.play();

//    sf::Music music;
//    if (!music.openFromFile("../resources/theircoming.ogg"))
//        return -1; // erreur
//    music.play();
    
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