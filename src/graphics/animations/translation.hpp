#ifndef TRANSLATION_ANIMATION_HPP_
#define TRANSLATION_ANIMATION_HPP_

#include "../animation.hpp"

enum TranslationType {Horizontal,Vertical};

class Translation : public Animation {
public:
    Translation(Blob* w, int interval, int speed, sf::Vector2f startPosition, sf::Vector2f endPosition,TranslationType t, int wait = 0);
    void update();
private:
    Blob* target;
    int speed;
    sf::Vector2f startPosition;
    sf::Vector2f endPosition;
    TranslationType type;
};

#endif // TRANSLATION_ANIMATION_HPP_"