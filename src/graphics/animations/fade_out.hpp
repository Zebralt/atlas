#ifndef FADE_OUT_ANIMATION_HPP_
#define FADE_OUT_ANIMATION_HPP_

#include "../animation.hpp"


class FadeOut : public Animation {
public:
    FadeOut(Blob* w, int interval,int f, int wait = 0);
    void update();
private:
    Blob* target;
    int thresh;
};

#endif // FADE_OUT_ANIMATION_HPP_