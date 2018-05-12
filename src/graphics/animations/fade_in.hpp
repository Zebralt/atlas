#ifndef FADE_IN_ANIMATION_HPP_
#define FADE_IN_ANIMATION_HPP_

#include "../animation.hpp"

class FadeIn : public Animation {
public:
    FadeIn(Blob* w, int interval, int f, int wait = 0 );
    void update();
private:
    Blob* target;
    int thresh;
};

#endif // FADE_IN_ANIMATION_HPP_