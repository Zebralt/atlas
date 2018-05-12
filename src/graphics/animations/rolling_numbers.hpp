#ifndef ROLLING_NUMBERS_ANIMATION_HPP_
#define ROLLING_NUMBERS_ANIMATION_HPP_

#include "../animation.hpp"

#include <SFML/Graphics/Text.hpp>

class RollingNumbers : public Animation {
public:
    RollingNumbers(sf::Text* target, int goal, int interval, int wait = 0);
    void update();
private:
    sf::Text* target;
    int size;
    int goal;

};

#endif // ROLLING_NUMBERS_ANIMATION_HPP_