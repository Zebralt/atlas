#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <SFML/Graphics.hpp>

#include "../model/temporary.hpp"

class Blob;

enum AnimationType {Fading,Movement,Scaling,Text,Value};

class Animation : public Temporary {
public:
    Animation(int interval, int wait = 0);
    bool isRunning();
    virtual void update() = 0;
    int getPast();

    virtual ~Animation() {}
protected:
    int interval;
    int past;
    sf::Clock clock;
};

class WaitAndBeStill : public Animation {
public:
    WaitAndBeStill(Blob* w, int wait);
    void update();
};

#endif // ANIMATION_HPP_
