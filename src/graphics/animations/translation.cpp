#include "translation.hpp"
#include "../graphic_obj.hpp"

/// TRANSLATION

Translation::Translation(Blob* w,int interval, int speed, sf::Vector2f startPosition, sf::Vector2f endPosition,TranslationType type, int wait) : Animation(interval,wait) {

    this->target = w;
    this->speed = speed;
    this->startPosition = startPosition;
    this->endPosition = endPosition;
    w->setPosition(startPosition);
    this->type = type;
}

void Translation::update() {
    int now = clock.getElapsedTime().asMilliseconds();
    if (isRunning() && now  - past >= interval) {

        if (type == TranslationType::Horizontal) {
            if (endPosition.x < startPosition.x) {
                if (target->getPosition().x > endPosition.x) {
                    target->setPosition(target->getPosition()-sf::Vector2f(speed,0));
                }
                else {
                    if (target->getPosition().x < endPosition.x)
                        target->setPosition(sf::Vector2f(endPosition.x,target->getPosition().y));
                    status = TERMINATED;
                    //std::cout << target->getPosition().x << ";" << target->getPosition().y << std::endl;
                }
            }
            else {
                if (target->getPosition().x < endPosition.x) {
                    target->setPosition(target->getPosition()+sf::Vector2f(speed,0));
                }
                else {
                    if (target->getPosition().x > endPosition.x)
                        target->setPosition(sf::Vector2f(endPosition.x,target->getPosition().y));
                    status = TERMINATED;
                    //std::cout << target->getPosition().x << ";" << target->getPosition().y << std::endl;
                }
            }
        }
        else if (type == TranslationType::Vertical) {
            if (endPosition.y < startPosition.y) {
                if (target->getPosition().y > endPosition.y) {
                    target->setPosition(target->getPosition()-sf::Vector2f(0,speed));
                }
                else {
                    if (target->getPosition().y < endPosition.y)
                        target->setPosition(sf::Vector2f(target->getPosition().x,endPosition.y));
                    status = TERMINATED;
                    //std::cout << target->getPosition().x << ";" << target->getPosition().y << std::endl;
                }
            }
            else {
                if (target->getPosition().y < endPosition.y) {
                    target->setPosition(target->getPosition()+sf::Vector2f(0,speed));
                }
                else {
                    if (target->getPosition().y > endPosition.y)
                        target->setPosition(sf::Vector2f(target->getPosition().x,endPosition.y));
                    status = TERMINATED;
                    //std::cout << target->getPosition().x << ";" << target->getPosition().y << std::endl;
                }
            }
        }
        past = now;
    }
}
